# Binary Clock --- Firmware Specification

## 1. Purpose

This project implements a binary clock on a microcrontroller as a learning experiment and for good times.

The intent is to gain handson experience with:
- GPIO configuration and control
- Hardware timers and interrupts
- Interrupt safe state handling
- Static memory utilization
- Basic hardware abstraciotn
- Translating a written specification into working firmware

---

### 2. High Level Behavior

The system displays the current time in hours and minutes using LEDs arranged in binary form.

- Time advances automatically once per second
- LEDs update to reflect the current time
- Buttons allow the user to adjust hours and minutes
- The system runs continuously while powered via USB

---

## 3. Hardware Platform

### 3.1 Microcontroller
- Target MCU: Raspberry Pi Pico (RP2040)
- CPU: Dual core ARM Cortext-MO+
- Clock source: default system clock (configured during startup)

Only one core will be used for this project.

---

### 3.2 Power
- Power source: USB (5v)
- No battery support (For Phase 1)
- No low power or sleep modes required.

---

### 3.3 Outputs (LEDs)

The clock uses LEDs to represent time in binary.

#### 3.3.1 Time Representation

- **Hours**
    - Range: 0-23
    - Represented using 5 LEDs (binary 00000-10111)

- ** MInutes**
    - Range: 0-59
    - Represented using 6 LEDs (binary 000000-111011)

Total LEDs: **11**

Each LED corresponds to one bit:
- Least significant bit (LSB) on the right
- Most significant bit (MSB) on the left

Exact physical layout is not critical but ought to be consistent and documented in code.

---

### 3.4 Inputs (Buttons)

Two momentary push buttons are used for time adjustment.

#### Button A - Increment Hours
- Each press increments the hour value by 1
- Hour wraps from 23 -> 0

#### Button B - Increment Minutes
- Each press increments the minute value by 1
- Minute wraps from 59 -> 0

Buttons are active low or active high depending on wiring. This must be handled correctly in firmware.

---

## Timekeeping

### 4.1 Time Base
- Time is tracked using a hardware timer interrupt
- Timer interval: **1 second**

### 4.2 Time variables
- Hours: integer [0, 23]
- Minutes: integer [0, 59]
- Seconds: integer [0, 59] (Not displayed)

### 4.3 Time Advancement
- Every time interrupt:
    - seconds++
    - If seconds == 60:
        - seconds = 0
        - minutes++
    - if minutes == 60:
        - minutes = 0
        - hours++
    - if hours == 24
        - hours = 0

---

## 5. Button Handling

### 5.1 Debounce Requirements
- Button inputs must be debounced in software
- Mechanical bounce must not cause multiple increments
- Debounce implementation may be:
    - time based
    - state machine based
    - interrupt + validation

Busy wait delays inside interrupts are not allwed.

---

### 5.2 Interaction with timekeeping
- Button presses modify time immediately
- Modifying minutes or hours does not affect seconds
- Button handling must be sfae with respect to the timer interrupt

---

## 6. Firmware Architecture

### 6.1 Execution Model
- Bare metal firmware
- No operating system
- No RTOS (Phase 1)

### 6.2 Main Loop
- The main loop must not block indefinitely
- No long busy wait delays
- The main loop is responsible for:
    - updating LED outputs
    - handling button state changes
    - responding to state updated by interrupts

---

### 6.3 Interrupts
- A hardware timer interrupt is used for 1 second ticks
- Interrupt handlers must:
    - be short
    - avoid blocking
    - avoid heavy computation
- Shared state between ISR and main code must be handled safely

---

### 7 Memory Management

### 3.1 Allocation Rules
- **No dynamic memory allocation**
- `malloc`, `free`, and related functions are not permitted
- All memory must be statically allocated

### 7.2 Stack Usage
- Stack usage must be kept small
- No deep recursion
- Stack size should be inspectable via the linker map

---

## 8. Coding Constraints and Style

- Language: C (C99 or later)
- Code must compile with warnings enabled
- Clear separation between:
  - hardware access
  - application logic
- Magic numbers should be avoided where practical
- Hardware register access must use `volatile` appropriately

---

## 9. Error Handling

- No user facing error display required
- System is expected to run indefinitely without crashing
- Undefined behavior must be avoided

---

## 10. Non-Goals

The following are explicitly out of scope:

- Real time clock (RTC) chip
- Persistent storage
- Battery operation
- Networking
- Displays (LCD/OLED)
- Configuration menus
- Power optimization
- Multi core usage

---

## 11. Success Criteria

The project is considered complete when:

- The clock reliably keeps time while powered
- LEDs correctly reflect the current time in binary
- Buttons adjust hours and minutes correctly
- Code is readable and documented
- Repository includes:
  - source code
  - this specification
  - a README explaining the project

---

## 12. Future Extensions (Optional)

These may be explored after completion, but are not required:

- Real time clock chip
- External display
- Battery power
- Improved LED layout
- Enclosure design