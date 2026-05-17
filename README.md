# vish_i2cdev — Low-Level I2C Library for Raspberry Pi Pico

## Overview

A minimal C++ I2C device library for the **Raspberry Pi Pico** (RP2040), built on top of the
[pico-sdk](https://github.com/raspberrypi/pico-sdk) `hardware_i2c` API. It wraps bus
initialization and register-based read/write into a simple class, making it easy to drive
I2C sensors and peripherals without boilerplate.

---

## Features

- Single-call bus initialization (pins, speed, pull-ups)
- Register-addressed blocking read and write
- Supports multi-byte register addresses (e.g., 16-bit register maps)
- Works with both `i2c0` and `i2c1`
- No dynamic memory allocation
- Designed to be subclassed by higher-level device drivers

---

## Integration

This library uses CMake. Add it as a subdirectory in your project:

```cmake
add_subdirectory(vish_i2cdev)
target_link_libraries(your_target vish_i2cdev)
```

Then include the header:

```cpp
#include "vish_i2cdev.h"
```

---

## API

### `begin()`

```cpp
bool begin(uint8_t* addr, i2c_inst_t* i2c_port, uint* speed,
           uint8_t* SDAPin, uint8_t* SCLPin, bool* PullUp_Enable);
```

Initializes the I2C peripheral and configures the GPIO pins.

| Parameter | Type | Description |
|---|---|---|
| `addr` | `uint8_t*` | 7-bit I2C device address |
| `i2c_port` | `i2c_inst_t*` | I2C instance — `i2c0` or `i2c1` |
| `speed` | `uint*` | Bus clock frequency in Hz (e.g. `400000` for Fast Mode) |
| `SDAPin` | `uint8_t*` | GPIO pin number for SDA |
| `SCLPin` | `uint8_t*` | GPIO pin number for SCL |
| `PullUp_Enable` | `bool*` | Enable internal pull-ups on SDA and SCL |

Returns `true` on success.

---

### `read()`

```cpp
void read(uint8_t* reg, uint8_t* dat, size_t len, size_t reg_len = 1);
```

Writes the register address to the device, then reads `len` bytes into `dat`.

| Parameter | Type | Description |
|---|---|---|
| `reg` | `uint8_t*` | Pointer to register address byte(s) |
| `dat` | `uint8_t*` | Buffer to store the received data |
| `len` | `size_t` | Number of bytes to read |
| `reg_len` | `size_t` | Number of register address bytes (default: `1`) |

---

### `write()`

```cpp
void write(uint8_t* reg, uint8_t* dat, size_t len, size_t reg_len = 1);
```

Writes the register address followed by `len` data bytes in a single I2C transaction.

| Parameter | Type | Description |
|---|---|---|
| `reg` | `uint8_t*` | Pointer to register address byte(s) |
| `dat` | `uint8_t*` | Data to write |
| `len` | `size_t` | Number of data bytes to write |
| `reg_len` | `size_t` | Number of register address bytes (default: `1`) |

---

## Example

```cpp
#include "pico/stdlib.h"
#include "vish_i2cdev.h"

vish_i2cdev sensor;

uint8_t addr        = 0x68;   // device I2C address
uint    speed       = 400000; // 400 kHz Fast Mode
uint8_t sda_pin     = 4;
uint8_t scl_pin     = 5;
bool    pullups     = true;

int main() {
    stdio_init_all();

    sensor.begin(&addr, i2c0, &speed, &sda_pin, &scl_pin, &pullups);

    // Write 0x01 to register 0x6B
    uint8_t reg  = 0x6B;
    uint8_t val  = 0x01;
    sensor.write(&reg, &val, 1);

    // Read 6 bytes starting from register 0x3B
    uint8_t data_reg = 0x3B;
    uint8_t buf[6];
    sensor.read(&data_reg, buf, 6);

    return 0;
}
```

---

## Dependencies

- [pico-sdk](https://github.com/raspberrypi/pico-sdk) — `pico_stdlib`, `hardware_i2c`

---

## License

MIT License. See LICENSE for details.
