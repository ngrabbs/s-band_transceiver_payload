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
src/
├── main.c                    # Entry point, initializes bus and tasks
├── init_tasks.c/h            # Calls launch_*_task() functions
├── bus_config.c/h            # SPI setup shared by all SPI devices

# Tasks (FreeRTOS)
├── task_radio.c/h            # Sends packets via SX1280 LoRa
├── task_can.c/h              # Receives/sends CAN messages
├── task_housekeeping.c/h     # Logs telemetry or internal status

# Peripheral Drivers
├── peripheral_lora1280.c/h   # C-style API to SX1280
├── peripheral_flash_spi.c/h  # (planned) External SPI flash storage
├── peripheral_mcp2515.c/h    # (planned) CAN transceiver driver

# Protocol Parsing / Abstraction
├── protocol_rf_command.c/h   # (planned) Handles high-level TX commands
├── protocol_spacecan.c/h     # (planned) Encodes/decodes SpaceCAN or CubeSat-specific protocols

# LoRa Driver Wrapping
├── SX1280.cpp/h              # Original C++ driver from NiceRF
├── sx1280_wrapper.cpp/h      # C-callable interface to SX1280 driver
```

---

## 📐 File Strategy Guidelines

### C vs C++
- Default language: **C**
- C++ is used only where necessary (e.g., SX1280 driver)
- Access C++ from C via `sx1280_wrapper.[cpp/h]`

### Layering
| Layer      | Example                      | Notes                                   |
|------------|------------------------------|-----------------------------------------|
| Task       | `task_radio.c`               | Runs `xQueueReceive`, calls drivers     |
| Peripheral | `peripheral_lora1280.c`      | Abstracts access to the radio           |
| Wrapper    | `sx1280_wrapper.cpp`         | Calls C++ driver via extern "C"         |
| Driver     | `SX1280.cpp`                 | Vendor code, untouched if possible      |

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
- [ ] CAN driver integration
- [ ] Protocol parsing (SpaceCAN or custom)
- [ ] Housekeeping/telemetry task

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
GNC, CubeSat@MSU  
June 2025