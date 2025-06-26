# S-Band Transceiver Payload

This project implements a modular FreeRTOS-based firmware for an RP2040-based CubeSat payload board. The board serves as a transceiver module that interfaces with both a CAN bus and a 2.4 GHz LoRa radio (NiceRF SX1280). It is designed to operate as a plug-in payload on any CubeSat platform that supports CAN communication and provides 3.3V power.

## 🎯 Project Purpose
- Receive command/control messages via CAN
- Decode and process those commands (e.g., transmit image, change LoRa settings)
- Transmit messages over LoRa
- Optionally receive LoRa messages and forward them back onto the CAN bus

## 🔁 High-Level Data Flow
```
+------------+       CAN         +------------------+      SPI       +-----------+
| Upstream   |  <------------>   | RP2040 Processor | <----------->  | SX1280 RF |
| OBC / IMU  |                   | (FreeRTOS)       |                | Module    |
+------------+                   +------------------+                +-----------+
```

---

## 🧱 Project Folder Structure

```
s-band_transceiver_payload/
├── CMakeLists.txt
├── include/                     # Public headers (available across modules)
│   ├── core/
│   ├── drivers/
│   ├── freertos/
│   ├── protocols/
│   ├── subsystems/
├── src/
│   ├── main.c                   # Entry point
│   ├── core/                    # Core services like config and messaging
│   │   ├── config.c
│   │   ├── message_queue.c
│   ├── freertos/                # Task definitions
│   │   ├── init_tasks.c
│   │   ├── task_can.c
│   │   ├── task_radio.c
│   │   ├── task_housekeeping.c
│   ├── drivers/                 # Low-level hardware interfaces
│   │   ├── spi/
│   │   ├── can/
│   │   ├── radio/
│   ├── subsystems/             # Subsystems like housekeeping, EPS, etc.
│   │   ├── housekeeping/
│   ├── protocols/              # Protocol-specific formatting and handlers
│   │   ├── protocol_rf_command.c
│   │   ├── protocol_spacecan.c
├── lib/                         # Third-party libraries (e.g. FreeRTOS)
```
## 📁 Header Layout

Public headers are now located in `include/`, separated from source files for clarity:

```
├── include/                     # Public headers (available across modules)
│   ├── core/
│   ├── drivers/
│   ├── freertos/
│   ├── protocols/
│   ├── subsystems/
```

These headers expose the task interfaces and peripheral APIs to `main.c` and other core logic.


---

## 📐 File Strategy Guidelines

### C vs C++
- Default language: **C**
- C++ is used only where necessary (e.g., SX1280 driver)
- Access C++ from C via `sx1280_wrapper.[cpp/h]`

### Layering
| Layer      | Example                               | Notes                                   |
|------------|---------------------------------------|-----------------------------------------|
| Task       | `freertos/task_radio.c`               | Runs `xQueueReceive`, calls drivers     |
| Peripheral | `drivers/radio/peripheral_lora1280.c` | Abstracts access to the radio           |
| Wrapper    | `drivers/radio/sx1280_wrapper.cpp`    | Calls C++ driver via extern "C"         |
| Driver     | `drivers/radio/SX1280.cpp`            | Vendor code, untouched if possible      |
| Config     | `core/config.c`                       | System config used across tasks         |
| Messaging  | `core/message_queue.c`                | Queues to pass data between tasks       |

### SPI Handling
- `init_spi()` in `bus_config.c` sets up SPI0 once
- Each SPI device uses its own CS pin
- Peripheral drivers do **not** call `spi_init()` — they assume it’s already done

---

## 🛠 Build Instructions
1. Clone with submodules:
   ```bash
   git clone --recurse-submodules <repo_url>
   cd s-band_transceiver_payload
   ```
2. Build:
   ```bash
   mkdir build && cd build
   cmake ..
   make -j
   ```

---

## ✅ Status
- [x] FreeRTOS setup and scheduler booting
- [x] SX1280 radio wrapped and transmitting
- [x] SPI shared bus config
- [x] CAN driver integration
- [x] Protocol parsing (SpaceCAN or custom)
- [x] Housekeeping/telemetry task
- [x] Inter-task message queue (FreeRTOS)

- [ ] CAN RX parsing and SpaceCAN injection
- [ ] Command decode / control via CAN or RF
- [ ] SPI flash or image buffer

---

## 📡 Goal
Make this module fully plug-and-play:
- Connects via standard CAN interface
- Accepts TX/RX commands via CAN
- Transmits LoRa messages at configurable parameters
- Optional onboard image storage via SPI flash

Designed for **maximum modularity** — this payload can go in *any CubeSat* that supports CAN and fits the form factor.

---

## 👨‍🚀 Author
**Nick Grabbs**  
June 2025