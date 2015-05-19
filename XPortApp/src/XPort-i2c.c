#include "XPort-i2c.h"
#include <unistd.h>

uint8_t getSDA(void) {

   int val;

   cp_config_data_input(SDA, &val);
   return(val);
}

uint8_t getSCL(void) {

   int val;

   cp_config_data_input(SCL, &val);
   return(val);
}

void i2c_dly(void) {

   usleep(2);	// 500 kHz clock
}

void i2c_init(void) {

   // set SDA,SCL pins as output
   cp_config_type_set (SDA, 1);
   cp_config_type_set (SCL, 1);

   setSDAhigh;
   setSCLhigh;   
}

void i2c_start(void) {

   setSDAhigh;
   i2c_dly();
   setSCLhigh;
   i2c_dly();
   setSDAlow;
   i2c_dly();
   setSCLlow;
   i2c_dly();
}

void i2c_stop(void) {

   setSDAlow;
   i2c_dly();
   setSCLhigh;
   i2c_dly();
   setSDAhigh;
   i2c_dly();
}

uint8_t i2c_read_byte(uint8_t ack) {

   uint8_t x, d = 0;

   setSDAhigh;
   
   // set SDA pin as input
   cp_config_type_set (SDA, 0);

   for (x=0; x<8; x++) {

      d <<= 1;
      do {
         setSCLhigh;
      } while (getSCL() == 0); // wait for any SCL clock stretching

      i2c_dly();

      if (getSDA())
         d |= 1;

      setSCLlow;
    }

    // set SDA pin as output
    cp_config_type_set (SDA, 1);

    if (ack) setSDAlow;
    else setSDAhigh;

    setSCLhigh;
    i2c_dly();
    setSCLlow;
    setSDAhigh;

    return d;
}

uint8_t i2c_write_byte(uint8_t byte) {

   uint8_t x, b;

   for (x=8; x; x--) {

      if (byte & 0x80) setSDAhigh;
         else setSDAlow;

      setSCLhigh;
      i2c_dly();
      byte <<= 1;
      setSCLlow;
      i2c_dly();
   }
  
   setSDAhigh;
   setSCLhigh;
   i2c_dly();

   b = getSDA(); // possible ACK bit
   setSCLlow;
 
   return b;
}
