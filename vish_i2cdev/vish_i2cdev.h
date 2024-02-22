#ifndef _VISH_I2CDEV_H
#define _VISH_I2CDEV_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

int return25();

class vish_i2cdev
{
    public:
    vish_i2cdev(uint8_t addr);

};

#endif // _VISH_I2CDEV_H