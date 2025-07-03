

# SX1280 Debugging and Configuration Saga

This document tracks all changes, experiments, and learnings related to getting the SX1280 radio working with our s-band_transceiver_payload project.

## Key Areas We Tested and Tweaked

- SPI wiring and MISO/MOSI directions
- Sleep vs. standby operation modes
- Bandwidth settings (e.g. 200kHz, 400kHz) and their register codes
- Spreading factor codes (e.g. LORA_SF7 = 0x70)
- Coding rates and register values
- Sync word settings:
    - Default SX1280 sync word: 0x1424
    [FC32 Capture Screenshot](./captures/915_MHz_lora_hat_good.png)
    - Experiments writing 0x0012 to registers 0x09C0 and 0x09C1
- Preamble length differences:
    - SX1280 defaulting to ~14 chirps
    - Adjusting preamble symbols to match RFM9x (8 chirps)
- Inverting IQ polarity to match waterfall chirp direction
- Matching payload length (payload_size)
- Integration with CAN bus commands to configure the radio
- RadioHead header bytes (0xFF, 0xFF, 0x00, 0x00) prepended to payloads
- Testing on different frequencies (e.g. 2.39 GHz vs. 2.4 GHz) to avoid interference
- SDR capture and inspectrum analysis:
    - Visualizing preamble and sync word differences
    - Verifying correct modulation parameters

This is a working document to capture ongoing progress and troubleshooting steps for future reference.