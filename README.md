# 🌱 ESP32 Digital Clock with Alarm System

An ESP32-based **Digital Clock and Alarm System** that automatically tracks precise real-time parameters via a hardware DS1307 RTC module and triggers an audible alert buzzer when a programmed schedule match occurs.  
The system displays real-time calendar updates, hours, minutes, seconds, and alarm diagnostic metrics on an I2C SSD1306 OLED display using custom I2C pin mapping.

---

## 📌 Project Overview

This project provides a robust utility framework for **smart home timepieces**, **automated instrumentation scheduling**, and **compact desk chronometers** by integrating dedicated real-time hardware logging with an ESP32 microcontroller.  
The RTC chip continuously updates tracking counts inside its independent quartz crystal logic ring.

- If the actual hours and minutes match the targeted preset constraints, the alarm buzzer turns **ON**
- Outside of that precise minute runtime layout boundary, the alarm buzzer remains **OFF**

The system displays:

- Calendar date stamp structures (DD/MM/YYYY)
- Standard highly legible real-time time frames (HH:MM:SS)
- Planned active target schedules and structural ringing diagnostics

on the crisp OLED screen layout.

---

## 🖼️ Circuit Diagram

![Circuit Diagram](circuit_diagram.png)

---

# 🛠️ Components Used

| Component                  | Quantity |
| -------------------------- | -------- |
| ESP32 Development Board    | 1        |
| DS1307 RTC Module (with CR2032) | 1   |
| I2C SSD1306 OLED Display (128x64) | 1 |
| Active Piezo Buzzer (5V/3.3V) | 1      |
| Jumper Wires               | As Required |

---

# ⚙️ Working Principle

1. The dedicated DS1307 Real-Time Clock calculates accurate time metrics using an isolated backup lithium cell.
2. The current register timestamps are transferred down to the ESP32 via custom defined digital I2C channels.
3. ESP32 strips the packet stream arrays into clean formatted date and hour character buffers.
4. Time analytics along with the next alarm benchmark parameters are printed on the OLED layout face.
5. If the time counter parameters cross into the user target alarm settings ($07:30$):
   - Output channel Pin 14 cycles dynamic voltage levels
   - The Piezo buzzer creates an active warning tone pattern
   - OLED renders a flashing "[RING!]" warning flag
6. When the minute interval advances past the preset schedule bounds:
   - Output alert channel Pin 14 drops back to zero
   - The Piezo buzzer returns to an inactive silent tracking profile

---

# 🔌 Pin Connections

Both the DS1307 RTC and the SSD1306 OLED share the primary custom I2C bus channels assigned on the ESP32.

## DS1307 RTC Module

| DS1307 Pin | ESP32 Pin |
| ---------- | ---------- |
| VCC        | 5V / 3V3   |
| GND        | GND        |
| SDA        | GPIO21     |
| SCL        | GPIO20     |

---

## Active Alarm Piezo Buzzer

| Buzzer Pin | ESP32 Pin |
| ---------- | ---------- |
| Positive(+) | GPIO14     |
| Negative(-) | GND        |

---

## I2C SSD1306 OLED Display

| OLED Pin | ESP32 Pin |
| -------- | ---------- |
| VCC      | 3V3        |
| GND      | GND        |
| SDA      | GPIO21     |
| SCL      | GPIO20     |

---

# 💻 Features

- ESP32 hardware tracking integration with autonomous power backups
- Dual-address synchronized execution profiles running on a shared custom I2C trunk line
- Beautiful typography scale presentations separating calendar structures from timers
- Secure data parsing using safe fixed character buffers (`timeBuffer[9]`, `dateBuffer[11]`, `alarmBuf[6]`)
- Integrated safety checks instantly resetting drift metrics during compilation if the clock stops

---

# 🧠 ESP32 Code Logic

The ESP32 performs the following tasks:

- Maintains stable communication links with two independent devices across custom hardware lines (`Wire.begin(21, 20)`)
- Unpacks raw byte matrices from internal hardware registers inside the DS1307 chip
- Runs logic checks matching system hours and minutes against hardcoded parameters
- Drives audible pulse tones through Piezo hardware arrays via pin GPIO14
- Re-renders structural character matrices onto the OLED window every 300 milliseconds

---

# 📊 Time Validation Logic

The target comparisons checking if the alarm tone circuit should trigger utilize standard logic equivalency equations:

```math
Alarm\ Alert \(= \begin{cases} Active, & \text{if } Hour_{now} == Hour_{alarm} \land Minute_{now} == Minute_{alarm} \\ Inactive, & \text{otherwise} \end{cases}\)
```

---

# 🚀 Installation Steps

1. Wire up the hardware cluster components precisely utilizing the custom I2C pin configurations (`SDA=21, SCL=20`).
2. Install required Arduino IDE framework extensions:
   - Wire.h
   - Adafruit_GFX.h
   - Adafruit_SSD1306.h
   - RTClib.h
3. Select your exact target ESP32 developer profile within the board configurations panel.
4. Upload the system executable code down onto the target chip board.
5. The device loop will immediately lock into sync tracking cycles and display interfaces.

---

# 📚 Required Libraries

```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"
```

Install the **RTClib**, **Adafruit SSD1306**, and **Adafruit GFX** frameworks inside your native Arduino Library Manager panel.

---

# 🔮 Future Improvements

- Over-the-Air (NTP) Network Time Protocol synchronization using native ESP32 Wi-Fi hardware
- Interactive web portal dashboard allowing custom remote alarm time adjustments
- Physical input push-button array integration enabling snooze configurations
- Bluetooth Low Energy (BLE) integration pairing profile interfaces for custom phone control
- Dual alarm banks supporting multi-tier schedule tracking parameters

---

# 🎯 Applications

- Standalone intelligent automated desk alarm clock appliances
- Automated sequence scheduling switches for smart grow spaces or labs
- Audio notification appliances for specialized workplace tracking routines
- Integrated backup chronometers for isolated offline instrumentation data logs

---

# 👨‍💻 Author

**Muhammad Zulqarnain**  
BS Intelligent Systems & Robotics

---

# 📄 License

This project is open-source and free to use for educational purposes.
