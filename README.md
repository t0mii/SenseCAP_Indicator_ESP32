# SenseCAP Indicator D1S - Extended Sensor Firmware

This is a modified firmware for the **SenseCAP Indicator D1S** that adds support for additional Grove sensors and MariaDB database export functionality.

## Extended Sensors

In addition to the original built-in sensors (SCD4x CO2, SGP40 TVOC), this firmware supports the following **Grove I2C sensors**:

| Sensor | Type | Measurements |
|--------|------|--------------|
| **Grove HM3301 (HM330X)** | Particulate Matter | PM1.0, PM2.5, PM10 (ug/m3) |
| **Grove Multichannel Gas Sensor V2** | Multi-Gas | NO2, C2H5OH (Ethanol), VOC, CO |
| **Grove AHT20** | External Temp/Humidity | Temperature (C), Humidity (%) |

### Sensor Summary

- **Internal Sensors** (built-in D1S):
  - SCD4x: CO2 (ppm), Temperature, Humidity
  - SGP40: TVOC Index

- **External Sensors** (Grove I2C, optional):
  - HM3301: PM1.0, PM2.5, PM10 particulate matter
  - Multichannel Gas V2: NO2, Ethanol, VOC, CO (raw voltage)
  - AHT20: External temperature and humidity

## Features

- [x] Time display with automatic timezone detection
- [x] Real-time sensor data display (4-page UI)
- [x] Historical data display (24h day view, 7-day week view)
- [x] WiFi configuration
- [x] Display configuration
- [x] Time configuration
- [x] **MariaDB/MySQL database export** (NEW)

## MariaDB Database Export

The firmware can automatically export sensor data to a MariaDB/MySQL database at configurable intervals.

### Configuration

Access the Database Export settings from the Settings menu:

- **Host**: Database server hostname or IP
- **Port**: Database port (default: 3306)
- **User**: Database username
- **Password**: Database password
- **Database**: Database name
- **Table**: Table name (auto-created if not exists)
- **Interval**: Export interval in minutes

### Database Schema

The firmware automatically creates a table with the following schema:

```sql
CREATE TABLE sensor_data (
    id INT AUTO_INCREMENT PRIMARY KEY,
    timestamp DATETIME,
    temp_internal FLOAT,
    humidity_internal FLOAT,
    co2 FLOAT,
    tvoc FLOAT,
    temp_external FLOAT,
    humidity_external FLOAT,
    pm1_0 FLOAT,
    pm2_5 FLOAT,
    pm10 FLOAT,
    no2_raw FLOAT,
    c2h5oh_raw FLOAT,
    voc_raw FLOAT,
    co_raw FLOAT
);
```

## Hardware Setup

### Required Components

1. SenseCAP Indicator D1S
2. Grove cables
3. Optional Grove sensors:
   - Grove HM3301 PM Sensor
   - Grove Multichannel Gas Sensor V2
   - Grove AHT20 Temperature & Humidity Sensor

### Wiring

Connect Grove sensors to the I2C Grove connectors on the SenseCAP Indicator. The RP2040 handles sensor communication via I2C.

## Building and Flashing

### Prerequisites

- ESP-IDF v5.1 or later
- PSRAM Octal 120M patch applied (see [patch instructions](../../tools/patch/README.md#idf-patch))

### ESP32-S3 (Main Firmware)

```bash
cd examples/indicator_basis
idf.py build
idf.py -p /dev/ttyACM0 flash monitor
```

### RP2040 (Sensor Coprocessor)

The RP2040 firmware is located in the companion repository:
- Repository: [SenseCAP_Indicator_RP2040](https://github.com/t0mii/SenseCAP_Indicator_RP2040)
- Path: `examples/indicator_rp2040/indicator_rp2040.ino`

Flash using Arduino IDE or arduino-cli with the Raspberry Pi Pico board support.

## UI Screenshots

The sensor display is organized into 4 pages:

1. **Environment**: External Temperature, Humidity, CO2, TVOC
2. **Particulate Matter**: PM1.0, PM2.5, PM10
3. **Gas Sensors**: NO2, C2H5OH, VOC, CO
4. **Internal Sensors**: Internal Temperature, Humidity

## License

Based on the original [SenseCAP Indicator](https://github.com/Seeed-Solution/SenseCAP_Indicator_ESP32) firmware by Seeed Studio.

## Credits

- Original firmware: [Seeed Studio](https://www.seeedstudio.com/)
- Extended sensor support and MariaDB export: Custom modifications
