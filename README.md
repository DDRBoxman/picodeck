# Picodeck

Firmware to use a Raspberry Pi Pico as a device in Elgato's Stream Deck software.

## Flashing

1. Grab the latest uf2 from the releases page, [here](https://github.com/DDRBoxman/picodeck/releases)
2. Press the BOOTSEL button and hold it while you connect the other end of the micro USB cable to your computer.
3. Drag the uf2 to the pico flash drive that shows up
4. Wait for it to reboot
5. Done!

## Wiring

#### Switches
Pins 2,3 switch 1
Pins 7,8 switch 2
Pins 12,13 switch 3

#### Neopixel (optional, shows the led color in settings)
Pin 34 neopixel data
Pin 40 neopixel power
Pin 38 neopixel ground

https://www.adafruit.com/product/1643

## Enclosure options

It should be trivial to wire this up to exisiting foot pedal hardware or arcade buttons.

I went a little overboard and built the foot switch that Adafruit shared:

https://learn.adafruit.com/three-button-foot-switch

## Development

### Building on macOS

```
brew tap ArmMbed/homebrew-formulae
brew install arm-none-eabi-gcc
mkdir build
cd build
cmake ..
```
