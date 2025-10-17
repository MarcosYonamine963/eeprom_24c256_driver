/*
 * 24C256N.h
 *
 *  Created on: Oct 16, 2025
 *      Author: McLovin
 */

#ifndef EEPROM_24C256_H_
#define EEPROM_24C256_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef void (*i2c_write_data_t)(uint8_t slave_addr, uint8_t data[], uint16_t len);
typedef void (*i2c_read_data_t) (uint8_t slave_addr, uint8_t data[], uint16_t len);

typedef struct
{
    i2c_write_data_t i2c_write_data;
    i2c_read_data_t i2c_read_data;
}eeprom_24c256_i2c_funcs_t;

typedef struct
{
    uint8_t slave_addr;
    eeprom_24c256_i2c_funcs_t i2c_funcs;
}eeprom_24c256_t;

typedef enum
{
    EEPROM_OK = 0,
    EEPROM_ERROR
}eeprom_24c256_status_t;

eeprom_24c256_status_t EEPROM_24C256_Write_Byte(eeprom_24c256_t *eeprom, uint16_t address, uint8_t data);
eeprom_24c256_status_t EEPROM_24C256_Read_Byte(eeprom_24c256_t *eeprom, uint16_t address, uint8_t *data);


#ifdef __cplusplus
}
#endif

#endif /* EEPROM_24C256_H_ */
