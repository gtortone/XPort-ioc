#include "cp_config.h"
#include <stdint.h>

#define SDA	1	// CP1
#define SCL	3	// CP3

#define setSDAhigh	cp_config_data_output(SDA, 1)
#define setSDAlow	cp_config_data_output(SDA, 0)

#define setSCLhigh	cp_config_data_output(SCL, 1)
#define setSCLlow	cp_config_data_output(SCL, 0)

#define ACK		1

uint8_t getSDA(void);
uint8_t getSCL(void);

void i2c_dly(void);

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);

uint8_t i2c_read_byte(uint8_t ack);
uint8_t i2c_write_byte(uint8_t byte);

