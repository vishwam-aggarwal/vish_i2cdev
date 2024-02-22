#include "vish_i2cdev.h"

vish_i2cdev::vish_i2cdev(uint8_t addr, bool i2cHW, uint32_t speed, uint8_t SDAPin, uint8_t SCLPin, bool PULLUP_Enable)
{
    _addr = addr;
    _i2cHW = i2cHW;
    _speed = speed;
    _SDAPin = SDAPin;
    _SCLPin = SCLPin;
    _PULLUP_Enable = PULLUP_Enable;
}

bool vish_i2cdev::begin()
{
    if (!_i2cHW)
    {
        i2c_init(i2c0, _speed);
    }
    else
    {
        i2c_init(i2c1, _speed);       
    }

    gpio_set_function(_SDAPin, GPIO_FUNC_I2C);
    gpio_set_function(_SCLPin, GPIO_FUNC_I2C);

    if(_PULLUP_Enable)
    {
        gpio_pull_up(_SDAPin);
        gpio_pull_up(_SCLPin);    
    }

    return true;
}