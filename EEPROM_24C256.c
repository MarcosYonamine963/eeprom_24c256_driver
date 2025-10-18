#include "EEPROM_24C256.h"

#ifndef NULL
#define NULL ((void *)0x00)
#endif

#define EEPROM_MAX_ADDR (0x7FFF)
#define EEPROM_SLV_ADDR_BASE (0b10100000)

static eeprom_24c256_status_t EEPROM24C256_Check_Instance(eeprom_24c256_t *eeprom)
{
    if(eeprom == NULL)
    {
        return EEPROM_ERROR;
    }

    if(eeprom->i2c_funcs.i2c_write_data == NULL)
    {
        return EEPROM_ERROR;
    }

    if(eeprom->i2c_funcs.i2c_read_data == NULL)
    {
        return EEPROM_ERROR;
    }

    return EEPROM_OK;
}

eeprom_24c256_status_t EEPROM_24C256_Write_Byte(eeprom_24c256_t *eeprom, uint16_t address, uint8_t data)
{
    if(EEPROM_ERROR == EEPROM24C256_Check_Instance(eeprom))
    {
        return EEPROM_ERROR;
    }

    if(address > EEPROM_MAX_ADDR)
    {
        return EEPROM_ERROR;
    }

    uint8_t slv_addr = EEPROM_SLV_ADDR_BASE;
    slv_addr |= ((eeprom->A2_PIN_LEVEL) << 3) | \
                ((eeprom->A1_PIN_LEVEL) << 2) | \
                ((eeprom->A0_PIN_LEVEL) << 1);

    uint8_t array[3];
    array[0] = (uint8_t)(address >> 8);
    array[1] = (uint8_t)(address);
    array[2] = data;

    eeprom->i2c_funcs.i2c_write_data(slv_addr, array, 3);

    return EEPROM_OK;
}

eeprom_24c256_status_t EEPROM_24C256_Read_Byte(eeprom_24c256_t *eeprom, uint16_t address, uint8_t *data)
{
    if(EEPROM_ERROR == EEPROM24C256_Check_Instance(eeprom))
    {
        return EEPROM_ERROR;
    }

    if(address > EEPROM_MAX_ADDR)
    {
        return EEPROM_ERROR;
    }

    uint8_t slv_addr = EEPROM_SLV_ADDR_BASE;
    slv_addr |= ((eeprom->A2_PIN_LEVEL) << 3) | \
                ((eeprom->A1_PIN_LEVEL) << 2) | \
                ((eeprom->A0_PIN_LEVEL) << 1);

    uint8_t array[2];
    array[0] = (uint8_t)(address >> 8);
    array[1] = (uint8_t)(address);

    eeprom->i2c_funcs.i2c_write_data(slv_addr, array, 2);
    eeprom->i2c_funcs.i2c_read_data(slv_addr, array, 1);

    *data = array[0];

    return EEPROM_OK;
}
