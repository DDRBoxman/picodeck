# Picodeck

Firmware to use a Raspberry Pi Pico as a device in Elgato's Stream Deck software.

<img src="https://user-images.githubusercontent.com/207897/178125108-f3028f94-14cd-44a7-9f3a-7141fb12fb62.jpg" width=35% height=35%>

## Flashing

1. Grab the latest uf2 from the releases page, [here](https://github.com/DDRBoxman/picodeck/releases)
2. Press the BOOTSEL button and hold it while you connect the other end of the micro USB cable to your computer.
3. Drag the uf2 to the pico flash drive that shows up
4. Wait for it to reboot
5. Done!

## Wiring

#### Switches
```
Pins 2,3 switch 1
Pins 7,8 switch 2
Pins 12,13 switch 3
```

#### Neopixel (optional, shows the led color in settings)
```
Pin 34 neopixel data
Pin 40 neopixel power
Pin 38 neopixel ground
```

I used the ring here:
https://www.adafruit.com/product/1643

## Enclosure options

It should be trivial to wire this up to exisiting foot pedal hardware or arcade buttons.

I went a little overboard and built the foot switch that Adafruit shared:

https://learn.adafruit.com/three-button-foot-switch

<img src="https://user-images.githubusercontent.com/207897/178125014-8a3d876b-2304-498d-8700-3da9c6ef965d.jpg" width=50% height=50%>
<img src="https://user-images.githubusercontent.com/207897/178125016-b806a085-701f-437a-9326-495bfbfd06e6.jpg" width=50% height=50%>

## Development

### Building on macOS

```
brew tap ArmMbed/homebrew-formulae
brew install arm-none-eabi
-gcc
mkdir build
cd build
cmake ..
```
