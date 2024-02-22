#ifndef _VISH_I2CDEV_H
#define _VISH_I2CDEV_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"

class vish_i2cdev
{
    public:
    vish_i2cdev();
    
    bool begin(uint8_t addr, i2c_inst_t* i2c_port = i2c0, uint32_t speed = 400*1000
        , uint8_t SDAPin = 1, uint8_t SCLPin = 2, bool PULLUP_Enable = false);

    void read(const uint8_t* reg, uint8_t* dat, size_t len);
    void write(const uint8_t* reg, uint8_t* dat, size_t len);

    private:
    uint8_t _addr;
    i2c_inst_t* _i2c_port;
    uint32_t _speed;
    uint8_t _SDAPin, _SCLPin;
    bool _PULLUP_Enable;

};

#endif // _VISH_I2CDEV_H