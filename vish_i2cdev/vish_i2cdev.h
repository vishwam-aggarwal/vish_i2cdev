#ifndef _VISH_I2CDEV_H
#define _VISH_I2CDEV_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"

class vish_i2cdev
{
    public:
    vish_i2cdev(uint8_t addr, bool i2cHW = 0, uint32_t speed = 400*1000
        , uint8_t SDAPin = 1, uint8_t SCLPin = 2, bool PULLUP_Enable = false);
    bool begin();

    private:
    uint8_t _addr;
    bool _i2cHW;
    uint32_t _speed;
    uint8_t _SDAPin, _SCLPin;
    bool _PULLUP_Enable;

};

#endif // _VISH_I2CDEV_H