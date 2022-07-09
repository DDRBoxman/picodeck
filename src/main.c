#include <stdio.h>
#include <stdlib.h>

#include "SEGGER_RTT.h"

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "bsp/board.h"
#include "tusb.h"

#define IS_RGBW false
#define NUM_PIXELS 12

#define WS2812_PIN 28

enum
{
    BLINK_NOT_MOUNTED = 250,
    BLINK_MOUNTED = 1000,
    BLINK_SUSPENDED = 2500,
};

static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

void led_blinking_task(void);
void neopixel_task(void);
void hid_task(void);

#define BUTTON_1_GPIO 1
#define BUTTON_2_GPIO 5
#define BUTTON_3_GPIO 9

static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) |
           ((uint32_t)(g) << 16) |
           (uint32_t)(b);
}

uint32_t ledColor = 0;
bool ledColorChanged = false;

int main()
{
    SEGGER_RTT_WriteString(0, "Hello World from SEGGER!\r\n");

    stdio_init_all();

    board_init();
    tusb_init();

    gpio_set_dir(BUTTON_1_GPIO, GPIO_IN);
    gpio_pull_up(BUTTON_1_GPIO);

    gpio_set_dir(BUTTON_2_GPIO, GPIO_IN);
    gpio_pull_up(BUTTON_2_GPIO);

    gpio_set_dir(BUTTON_3_GPIO, GPIO_IN);
    gpio_pull_up(BUTTON_3_GPIO);

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    put_pixel(urgb_u32(255, 0, 0));

    while (1)
    {
        tud_task(); // tinyusb device task
        led_blinking_task();

        neopixel_task();

        hid_task();
    }
    return 0;
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
    blink_interval_ms = BLINK_MOUNTED;
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
    blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
    (void)remote_wakeup_en;
    blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
    blink_interval_ms = BLINK_MOUNTED;
}

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

// uint8_t report[7] = {0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00};

// Every 10ms, we will sent 1 report for each HID profile (keyboard, mouse etc ..)
// tud_hid_report_complete_cb() is used to send the next report after previous one is complete
void hid_task(void)
{
    // Poll every 10ms
    const uint32_t interval_ms = 100;
    static uint32_t start_ms = 0;

    if (board_millis() - start_ms < interval_ms)
        return; // not enough time

    start_ms += interval_ms;

    if (!tud_hid_ready())
        return;

    uint8_t report[7] = {0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00};

    report[3] = !gpio_get(BUTTON_1_GPIO);
    report[4] = !gpio_get(BUTTON_2_GPIO);
    report[5] = !gpio_get(BUTTON_3_GPIO);

    // send pedal hid report
    tud_hid_report(1, &report, 7);
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const *report, uint8_t len)
{
    (void)instance;
    (void)report;
    (void)len;
}

// 2.0.2.8
uint8_t version[15] = {0x0C, 0xD9, 0x4B, 0x72, 0xE0, 0x32, 0x2E, 0x30, 0x2E, 0x32, 0x2E, 0x38, 0x00, 0x00, 0x00};

// ZZZZZZZZZZZZZ
uint8_t serial[15] = {0x0C, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x00, 0x00};

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen)
{
    (void)instance;
    (void)buffer;
    (void)reqlen;

    char str[80];

    sprintf(str, "GET Report Type: %d, Report ID: %d\r\n", report_type, report_id);

    SEGGER_RTT_WriteString(0, str);

    if (report_type == HID_REPORT_TYPE_FEATURE)
    {

        if (report_id == 0x05)
        {
            // version
            memcpy(buffer, version, reqlen);
            return 31;
        }
        if (report_id == 0x06)
        {
            // serial
            memcpy(buffer, serial, reqlen);
            return 31;
        }
    }

    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize)
{
    (void)instance;

    char str[80];

    sprintf(str, "SET instance: %d, Report Type: %d, Report ID: %d, len: %d\r\n", instance, report_type, report_id, bufsize);

    SEGGER_RTT_WriteString(0, str);

    if (report_type == 0 && report_id == 0)
    {

        // LED Color
        if (buffer[0] == 0x02 && buffer[1] == 0x0b)
        {
            blink_interval_ms = 50;

            sprintf(str, "RGB: %02X%02X%02X\r\n", buffer[2], buffer[3], buffer[4]);

            SEGGER_RTT_WriteString(0, str);

            ledColor = urgb_u32(buffer[2], buffer[3], buffer[4]);
            ledColorChanged = true;
        }
    }

    if (report_type == HID_REPORT_TYPE_FEATURE)
    {

        if (report_id == 0x03)
        {
            // reset?
            // blink_interval_ms = 100;
        }
    }

    if (report_type == HID_REPORT_TYPE_OUTPUT)
    {
    }
}

//--------------------------------------------------------------------+
// BLINKING TASK
//--------------------------------------------------------------------+
void led_blinking_task(void)
{
    static uint32_t start_ms = 0;
    static bool led_state = false;

    // blink is disabled
    if (!blink_interval_ms)
        return;

    // Blink every interval ms
    if (board_millis() - start_ms < blink_interval_ms)
        return; // not enough time

    start_ms += blink_interval_ms;

    board_led_write(led_state);
    led_state = 1 - led_state; // toggle
}

void neopixel_task(void)
{
    // todo: something cooler here than just setting all leds to the specified color

    if (ledColorChanged)
    {
        ledColorChanged = false;

        for (int i = 0; i < NUM_PIXELS; ++i)
        {
            put_pixel(ledColor);
        }
    }
}