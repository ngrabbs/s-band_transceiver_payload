             +--------------------+
             |   config.c         |
             | (startup defaults) |
             +---------+----------+
                       |
        Startup        |
         config        |
                       v
             +---------+----------+
             |    init_tasks.c    |
             +---------+----------+
                       |
                       v
         +-------------+---------------+
         |     message_queue_send()    |
         +-------------+---------------+
                       |
                       v
             +---------+---------+
             |    task_radio.c   |
             +---------+---------+
                       |
                       v
             +---------+---------+
             |     radio_hal.c   |
             +---------+---------+
                       |
                       v
             +---------+---------+
             | peripheral_lora1280.c |
             +---------+---------+
                       |
                       v
             +---------+---------+
             |   sx1280_wrapper.c |
             +---------+---------+
                       |
                       v
             +---------+---------+
             |     SX1280.cpp    |
             +---------+---------+
                       |
                       v
             +---------+---------+
             |   SPI hardware    |
             +-------------------+

-------------------------------------------------------

             +--------------------+
             |      CAN RX        |
             |     (task_can.c)   |
             +---------+----------+
                       |
                       v
             +---------+----------+
             | protocol_spacecan.c|
             +---------+----------+
                       |
                       v
         +-------------+---------------+
         |     message_queue_send()    |
         +-------------+---------------+
                       |
                       v
             +---------+---------+
             |    task_radio.c   |
             +---------+---------+
                       |
                       v
             +---------+---------+
             |     radio_hal.c   |
             +---------+---------+
                       |
                       v
             +---------+---------+
             | peripheral_lora1280.c |
             +---------+---------+
                       |
                       v
             +---------+---------+
             |   sx1280_wrapper.c |
             +---------+---------+
                       |
                       v
             +---------+---------+
             |     SX1280.cpp    |
             +---------+---------+
                       |
                       v
             +---------+---------+
             |   SPI hardware    |
             +-------------------+

## radio_hal.c Responsibilities

The **radio_hal.c** module is responsible for:

- Presenting a **common radio API** for higher-level code (tasks, protocols).
- Deciding which radio driver (RFM9x, SX1280, etc.) to use, based on `sys_config.radio_type`.
- Calling functions in peripheral drivers, like:
  - `lora1280_set_frequency()`
  - `lora1280_set_power()`
  - etc.
- Centralizing debug logs related to radio operations.

**radio_hal.c does NOT:**

- Perform direct SPI register writes itself.
- Contain hardware-specific implementation details.

Instead, it **delegates** to the peripheral drivers (e.g. `peripheral_lora1280.c`) which handle the low-level hardware calls and ultimately communicate via SPI through wrapper classes like `sx1280_wrapper.c` and `SX1280.cpp`.

This separation ensures the rest of the system remains hardware-agnostic while keeping hardware-specific logic isolated.