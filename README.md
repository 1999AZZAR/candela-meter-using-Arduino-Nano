# Light Sensing and Direction Detection System (Candela Meter) using Arduino Nano

## Table of content

1. [Introduction](#introduction)
2. [Components](#components)
3. [Libraries](#libraries)
4. [Pin Configuration](#pin-configuration)
5. [Functionality](#functionality)
6. [Version](#version)
7. [Usage](#usage)
8. [Support](#support)

## Introduction

This project involves creating a light sensing and direction detection system using an Arduino Nano microcontroller. The system uses Light Dependent Resistors (LDRs) to measure light levels in different directions and displays the results on a 20x4 character I2C LCD screen.

## Components

To build this system, you'll need the following hardware components:

- Arduino Nano
- 20x4 I2C LCD screen
- Four LDRs
- Two push buttons for menu navigation
- Voltage and distance sensors (here we use two potentiometers as analog sensors)
- Appropriate power source for the Arduino Nano

## Libraries

The code utilizes two libraries:

- Wire.h: For I2C communication with the LCD screen.
- LiquidCrystal_I2C.h: To interface with and control the I2C-connected LCD screen.

## Pin Configuration

Here's how the Arduino Nano is connected to various components:

- LDRs:
  - Top LDR: Analog pin A0
  - Right LDR: Analog pin A1
  - Bottom LDR: Analog pin A2
  - Left LDR: Analog pin A3
- Voltage measurement: Analog pin A6
- Distance measurement: Analog pin A7
- Menu navigation buttons:
  - Button 1: Digital pin 2
  - Button 2: Digital pin 3
- I2C-connected LCD screen:
  - LCD Address: 0x27
  - LCD Dimensions: 20x4 characters

## Functionality

The system operates as follows:

- It continuously reads values from the LDRs, voltage sensor, and distance sensor at regular intervals.
- Normalizes and maps the sensor readings to calculate lux, voltage, and distance values.
- Uses these values to calculate the candela value for each direction (Top, Right, Bottom, and Left).
- Determines the dominant direction based on the highest candela value.
- Displays the calculated candela values and the dominant direction on the LCD screen.
- Provides two menus: Home (average candela and dominant direction) and Sensor Values (individual candela values).
- Menu navigation is achieved using two push buttons.

## Version

- [code 1](code/code%201)
- [code 2](code/code%202)

## Usage

To use this system:

1. Upload the provided code to your Arduino Nano using the Arduino IDE or compatible software.
2. Connect the components according to the specified pin configuration.
3. Power up the Arduino Nano.
4. The system will display calculated values on the LCD screen, and you can switch between Home and Sensor Values menus using the push buttons.

## Support

You can support me by buy me a coffee if u like to.

<div align="left">
<!--   <h4>And you can also support me by <a href="https://www.buymeacoffee.com/azzar" target="_blank">buying me coffee</a></h4> -->
  <a href="https://www.buymeacoffee.com/azzar" target="_blank">
    <img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 42px !important;width: 151.9px !important; margin-top: 50px !important;">
  </a>
</div>
