# 7SegmentLED > Year 1 PaDI Final Project

## Overview

This project drives a single 7-segment display through a custom `DisplaySystem` class, with four independent buttons each mapped to their own interrupt callback, semaphore, and dedicated thread. A `Mutex` (`processKey`) ensures only one thread can write to the display at a time, preventing race conditions. On boot, the display runs a startup animation before entering its idle state.

## Hardware

- Nucleo G071RB
- 1X Common Cathode 7-segment display
- 4x push buttons:
  - `A0` — Custom Text
  - `A1` — First Name
  - `A2` — Last Name
  - `BUTTON1` — Print Delay

## Project Structure

```
7SegmentLED/
├── main.cpp          # Interrupt setup, thread definitions, main entry point
└── displaySysLib/     # DisplaySystem class (display driving, custom text, delay control)
```

## Usage

1. Power on the board — a startup animation plays on the display.
2. Press a button to trigger its corresponding action:
   - **Custom Text button** — first press prompts you to enter custom text; subsequent presses display it
   - **First Name button** — displays first name
   - **Last Name button** — displays last name
   - **Print Delay button** — adjusts the display timing rather than showing text
