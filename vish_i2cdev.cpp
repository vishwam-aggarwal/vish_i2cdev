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

void vish_i2cdev::read(uint8_t* reg, uint8_t* dat, size_t len, size_t reg_len)
{
    uint8_t Reg[reg_len];
    for(uint8_t i=0; i<(reg_len); i++)
    {
        Reg[i] = *(reg + i);
    }    
    i2c_write_blocking(_i2c_port, *_addr, &Reg[0], reg_len, true); 
    i2c_read_blocking(_i2c_port, *_addr, dat, len, false);

}

void vish_i2cdev::write(uint8_t* reg, uint8_t* dat, size_t len, size_t reg_len)
{
    uint8_t Data[len+reg_len];
    for(uint8_t i=0; i<(reg_len); i++)
    {
        Data[i] = *(reg + i);
    }
    for(uint8_t j=0; j<(len); j++)
    {
        Data[reg_len+j] = *(dat + j);
    }
    i2c_write_blocking(_i2c_port, *_addr, &Data[0], len+1, false); 
}