/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "tusb.h"

#define USB_PID   0x0086

#define USB_VID   0x0fd9
#define USB_BCD   0x0200

//--------------------------------------------------------------------+
// Device Descriptors
//--------------------------------------------------------------------+
tusb_desc_device_t const desc_device =
{
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = USB_BCD,
    .bDeviceClass       = 0x00,
    .bDeviceSubClass    = 0x00,
    .bDeviceProtocol    = 0x00,
    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,

    .idVendor           = USB_VID,
    .idProduct          = USB_PID,
    .bcdDevice          = 0x0100,

    .iManufacturer      = 0x01,
    .iProduct           = 0x02,
    .iSerialNumber      = 0x03,

    .bNumConfigurations = 0x01
};

// Invoked when received GET DEVICE DESCRIPTOR
// Application return pointer to descriptor
uint8_t const * tud_descriptor_device_cb(void)
{
  return (uint8_t const *) &desc_device;
}

//--------------------------------------------------------------------+
// HID Report Descriptor
//--------------------------------------------------------------------+

#define TUD_HID_REPORT_DESC_PEDAL() \
HID_USAGE_PAGE ( HID_USAGE_PAGE_CONSUMER    ), \
HID_USAGE      ( HID_USAGE_CONSUMER_CONTROL ), \
HID_COLLECTION ( HID_COLLECTION_APPLICATION ), \
    HID_USAGE_PAGE_N(HID_USAGE_PAGE_VENDOR, 2), \
      HID_LOGICAL_MIN  ( 0 ), \
      HID_LOGICAL_MAX  ( 0xFF ), \
      HID_REPORT_SIZE  ( 8 ), \
      HID_REPORT_COUNT_N( 1023, 2) , \
      HID_REPORT_ID    ( 2 ) \
      HID_OUTPUT       ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE | HID_WRAP_NO | HID_LINEAR | HID_PREFERRED_STATE | HID_NO_NULL_POSITION | HID_NON_VOLATILE ) ,\
    HID_USAGE_PAGE_N(HID_USAGE_PAGE_VENDOR, 2), \
      HID_LOGICAL_MIN  ( 0 ), \
      HID_LOGICAL_MAX  ( 0xFF ), \
      HID_REPORT_SIZE  ( 8 ), \
      HID_REPORT_COUNT ( 7 ), \
      HID_REPORT_ID    (0x01) \
      HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE| HID_WRAP_NO | HID_LINEAR | HID_PREFERRED_STATE | HID_NO_NULL_POSITION ), \
    HID_USAGE_PAGE_N(HID_USAGE_PAGE_VENDOR, 2), \
      HID_LOGICAL_MIN  ( 0 ), \
      HID_LOGICAL_MAX  ( 0xFF ), \
      HID_REPORT_SIZE  ( 8 ), \
      HID_REPORT_COUNT ( 31 ), \
      HID_REPORT_ID    (0x03) \
      HID_FEATURE      ( HID_DATA | HID_ARRAY | HID_RELATIVE | HID_WRAP_NO | HID_LINEAR | HID_PREFERRED_STATE | HID_NO_NULL_POSITION | HID_NON_VOLATILE ), \
    HID_USAGE_PAGE_N(HID_USAGE_PAGE_VENDOR, 2), \
      HID_LOGICAL_MIN  ( 0 ), \
      HID_LOGICAL_MAX  ( 0xFF ), \
      HID_REPORT_SIZE  ( 8 ), \
      HID_REPORT_COUNT ( 31 ), \
      HID_REPORT_ID    (0x06) \
      HID_FEATURE      ( HID_DATA | HID_ARRAY | HID_RELATIVE | HID_WRAP_NO | HID_LINEAR | HID_PREFERRED_STATE | HID_NO_NULL_POSITION | HID_NON_VOLATILE ), \
    HID_USAGE_PAGE_N(HID_USAGE_PAGE_VENDOR, 2), \
      HID_LOGICAL_MIN  ( 0 ), \
      HID_LOGICAL_MAX  ( 0xFF ), \
      HID_REPORT_SIZE  ( 8 ), \
      HID_REPORT_COUNT ( 31 ), \
      HID_REPORT_ID    (0x07) \
      HID_FEATURE      ( HID_DATA | HID_ARRAY | HID_RELATIVE | HID_WRAP_NO | HID_LINEAR | HID_PREFERRED_STATE | HID_NO_NULL_POSITION | HID_NON_VOLATILE ), \
    HID_USAGE_PAGE_N(HID_USAGE_PAGE_VENDOR, 2), \
      HID_LOGICAL_MIN  ( 0 ), \
      HID_LOGICAL_MAX  ( 0xFF ), \
      HID_REPORT_SIZE  ( 8 ), \
      HID_REPORT_COUNT ( 31 ), \
      HID_REPORT_ID    (0x05) \
      HID_FEATURE      ( HID_DATA | HID_ARRAY | HID_RELATIVE | HID_WRAP_NO | HID_LINEAR | HID_PREFERRED_STATE | HID_NO_NULL_POSITION | HID_NON_VOLATILE ), \
    HID_USAGE_PAGE_N(HID_USAGE_PAGE_VENDOR, 2), \
      HID_LOGICAL_MIN  ( 0 ), \
      HID_LOGICAL_MAX  ( 0xFF ), \
      HID_REPORT_SIZE  ( 8 ), \
      HID_REPORT_COUNT ( 31 ), \
      HID_REPORT_ID    (0x04) \
      HID_FEATURE      ( HID_DATA | HID_ARRAY | HID_RELATIVE | HID_WRAP_NO | HID_LINEAR | HID_PREFERRED_STATE | HID_NO_NULL_POSITION | HID_NON_VOLATILE ), \
    HID_USAGE_PAGE_N(HID_USAGE_PAGE_VENDOR, 2), \
      HID_LOGICAL_MIN  ( 0 ), \
      HID_LOGICAL_MAX  ( 0xFF ), \
      HID_REPORT_SIZE  ( 8 ), \
      HID_REPORT_COUNT ( 31 ), \
      HID_REPORT_ID    (0x08) \
      HID_FEATURE      ( HID_DATA | HID_ARRAY | HID_RELATIVE | HID_WRAP_NO | HID_LINEAR | HID_PREFERRED_STATE | HID_NO_NULL_POSITION | HID_NON_VOLATILE ), \
    HID_COLLECTION_END \

uint8_t const desc_hid_report[] =
{
  TUD_HID_REPORT_DESC_PEDAL()
};

// Invoked when received GET HID REPORT DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const * tud_hid_descriptor_report_cb(uint8_t instance)
{
  (void) instance;
  return desc_hid_report;
}

//--------------------------------------------------------------------+
// Configuration Descriptor
//--------------------------------------------------------------------+

enum
{
  ITF_NUM_HID,
  ITF_NUM_TOTAL
};

#define  CONFIG_TOTAL_LEN  (TUD_CONFIG_DESC_LEN + TUD_HID_INOUT_DESC_LEN)

#define EPNUM_HID   0x01

uint8_t const desc_configuration[] =
{
  // Config number, interface count, string index, total length, attribute, power in mA
  TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 100),

   // Interface number, string index, protocol, report descriptor len, EP In & Out address, size & polling interval
  TUD_HID_INOUT_DESCRIPTOR(ITF_NUM_HID, 0, HID_PROTOCOL_REPORT, sizeof(desc_hid_report), EPNUM_HID, 0x80 | EPNUM_HID, CFG_TUD_HID_EP_BUFSIZE, 1)
};

#if TUD_OPT_HIGH_SPEED
// Per USB specs: high speed capable device must report device_qualifier and other_speed_configuration

// other speed configuration
uint8_t desc_other_speed_config[CONFIG_TOTAL_LEN];

// device qualifier is mostly similar to device descriptor since we don't change configuration based on speed
tusb_desc_device_qualifier_t const desc_device_qualifier =
{
  .bLength            = sizeof(tusb_desc_device_qualifier_t),
  .bDescriptorType    = TUSB_DESC_DEVICE_QUALIFIER,
  .bcdUSB             = USB_BCD,

  .bDeviceClass       = 0x00,
  .bDeviceSubClass    = 0x00,
  .bDeviceProtocol    = 0x00,

  .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,
  .bNumConfigurations = 0x01,
  .bReserved          = 0x00
};

// Invoked when received GET DEVICE QUALIFIER DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete.
// device_qualifier descriptor describes information about a high-speed capable device that would
// change if the device were operating at the other speed. If not highspeed capable stall this request.
uint8_t const* tud_descriptor_device_qualifier_cb(void)
{
  return (uint8_t const*) &desc_device_qualifier;
}

// Invoked when received GET OTHER SEED CONFIGURATION DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
// Configuration descriptor in the other speed e.g if high speed then this is for full speed and vice versa
uint8_t const* tud_descriptor_other_speed_configuration_cb(uint8_t index)
{
  (void) index; // for multiple configurations

  // other speed config is basically configuration with type = OHER_SPEED_CONFIG
  memcpy(desc_other_speed_config, desc_configuration, CONFIG_TOTAL_LEN);
  desc_other_speed_config[1] = TUSB_DESC_OTHER_SPEED_CONFIG;

  // this example use the same configuration for both high and full speed mode
  return desc_other_speed_config;
}

#endif // highspeed

// Invoked when received GET CONFIGURATION DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const * tud_descriptor_configuration_cb(uint8_t index)
{
  (void) index; // for multiple configurations

  // This example use the same configuration for both high and full speed mode
  return desc_configuration;
}

//--------------------------------------------------------------------+
// String Descriptors
//--------------------------------------------------------------------+

// array of pointer to string descriptors
char const* string_desc_arr [] =
{
  (const char[]) { 0x09, 0x04 }, // 0: is supported language is English (0x0409)
  "Elgato",                     // 1: Manufacturer
  "Stream Deck Pedal",              // 2: Product
  "ZZZZZZZZZZZZZ",                      // 3: Serials, should use chip ID
};

static uint16_t _desc_str[32];

// Invoked when received GET STRING DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid)
{
  (void) langid;

  uint8_t chr_count;

  if ( index == 0)
  {
    memcpy(&_desc_str[1], string_desc_arr[0], 2);
    chr_count = 1;
  }else
  {
    // Note: the 0xEE index string is a Microsoft OS 1.0 Descriptors.
    // https://docs.microsoft.com/en-us/windows-hardware/drivers/usbcon/microsoft-defined-usb-descriptors

    if ( !(index < sizeof(string_desc_arr)/sizeof(string_desc_arr[0])) ) return NULL;

    const char* str = string_desc_arr[index];

    // Cap at max char
    chr_count = strlen(str);
    if ( chr_count > 31 ) chr_count = 31;

    // Convert ASCII string into UTF-16
    for(uint8_t i=0; i<chr_count; i++)
    {
      _desc_str[1+i] = str[i];
    }
  }

  // first byte is length (including header), second byte is string type
  _desc_str[0] = (TUSB_DESC_STRING << 8 ) | (2*chr_count + 2);

  return _desc_str;
}
