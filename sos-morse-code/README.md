# SOS in Morse Code with Arduino  

## Overview  

This project demonstrates how to emit the word **SOS** in Morse code using an Arduino, a push button, and an LED.  
When the button is pressed, the Arduino turns the LED on and off in the correct timing pattern for Morse code.  

The goal of this challenge is to help students practice digital I/O handling, timing with delays, and basic electronics concepts using Arduino.  

-----

## Hardware Setup  

  - **Button** connected to **digital pin 6** (chosen arbitrarily).  
  - **LED** connected to **digital pin 7** (chosen arbitrarily).  
  - **10kΩ resistor** used as a pull-down resistor for the button.  
  - **330Ω resistor** used in series with the LED to limit current.  

-----

## Why a 10kΩ Resistor for the Button?  

When no resistor is used, the input pin can "float" and randomly switch between HIGH and LOW due to electrical noise.  
A **10kΩ resistor** is a common and safe value for pull-down (or pull-up) resistors:  

  - Small enough to keep the input stable at **LOW** when the button is not pressed.  
  - Large enough to avoid wasting unnecessary current when the button is pressed.  

-----

## Why a 330Ω Resistor for the LED?  

Arduino pins can source or sink up to **40mA**, but the safe recommended operating current for an LED is **10–20mA**.  
This resistor value ensures the LED operates safely and efficiently. 💡 For a more complete documentation with all the calculations, check the **[document.html](./document.html)** file.

-----

## How It Works  

  - Pressing the button triggers the Arduino to emit **SOS** in Morse code.  
  - **S = ...** (three dots)  
  - **O = ---** (three dashes)  
  - Timing follows Morse code rules:  
      - Dot = LED ON for 200 ms  
      - Dash = LED ON for 600 ms  
      - Spaces handled with OFF delays  