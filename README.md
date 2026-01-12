# Binary Clock (Firmware Learning Project)

This repository contains a bare metal binary clock implemented on a microcontroller.

The goal of this project is to learn and demonstrate
core firmware concepts close to the hardware, including:

- GPIO configuration and control
- Timers and interrupts
- Interrupt safe state management
- Static memory usage and layout
- Basic hardware abstraction
- Reading and applying microcontroller datasheets

This project is intentionally simple in scope and avoids unnecessary features in order to
focus on correctness, clarity, and understanding.

---

## Project Scope

The binary clock:
- Displays time (hours and minutes) in binary using LEDs
- Uses a hardware timer to track time
- Uses buttons to adjust hours and minutes
- Runs without an operating system
- Is powered via USB

Non-goals:
- No display screens
- No networking
- No battery optimization
- No real time clock (RTC) chip
- No OS or RTOS (initial version)

---

## Hardware

Target platform:
- Microcontroller: Raspberry Pi Pico (RP2040)

Additional components:
- LEDs with current limiting resistors
- Push buttons
- Breadboard and jumper wires

---

## Repository Structure (initial)
binaryclock/

├── README.md

├── docs/

│ └── spec.md

├── src/

├── include/

└── notes/

This structure may evolve as the project grows.

---

## Status

- [ ] Toolchain setup
- [ ] Single LED blink
- [ ] Multiple GPIO outputs
- [ ] Timer interrupt
- [ ] Binary time display
- [ ] Button input
- [ ] Debounce logic
- [ ] Refactor and cleanup
- [ ] Documentation

---

## Why This Exists

This project is part of a larger effort to move from application level software
toward embedded firmware and systems programming.

The emphasis is on understanding *why* the system works, not just *that* it works
