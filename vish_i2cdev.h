#ifndef _VISH_I2CDEV_H
#define _VISH_I2CDEV_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"

class vish_i2cdev
{
    public:
    vish_i2cdev();
    
    bool begin(uint8_t* addr, i2c_inst_t* i2c_port, uint* speed,
                uint8_t* SDAPin, uint8_t* SCLPin, bool* PULLUP_Enable);

    void read(uint8_t* reg, uint8_t* dat, size_t len, size_t reg_len = 1);
    void write(uint8_t* reg, uint8_t* dat, size_t len, size_t reg_len = 1);

    private:
    i2c_inst_t* _i2c_port;
    uint8_t* _addr;
};

#endif // _VISH_I2CDEV_H