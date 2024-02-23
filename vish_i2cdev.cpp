#include "vish_i2cdev.h"

vish_i2cdev::vish_i2cdev()
{
}

bool vish_i2cdev::begin(uint8_t* addr, i2c_inst_t* i2c_port, uint* speed, uint8_t* SDAPin, uint8_t* SCLPin, bool* PULLUP_Enable)
{
    _i2c_port = i2c_port;
    _addr = addr;

    i2c_init(i2c_port, *speed);

    gpio_set_function(*SDAPin, GPIO_FUNC_I2C);
    gpio_set_function(*SCLPin, GPIO_FUNC_I2C);

    if(*PULLUP_Enable)
    {
        gpio_pull_up(*SDAPin);
        gpio_pull_up(*SCLPin);    
    }

    return true;
}

void vish_i2cdev::read(const uint8_t* reg, uint8_t* dat, size_t len)
{
    i2c_write_blocking(_i2c_port, *_addr, reg, 1, true);
    i2c_read_blocking(_i2c_port, *_addr, dat, len, false);

}

void vish_i2cdev::write(const uint8_t* reg, uint8_t* dat, size_t len)
{
    uint8_t Data[len+1];
    Data[0] = *reg;
    for(uint8_t i=0; i<(len); i++)
    {
        Data[i+1] = *(dat + i);
    }
    i2c_write_blocking(_i2c_port, *_addr, &Data[0], len+1, false); 
}