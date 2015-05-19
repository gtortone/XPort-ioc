#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <devSup.h>
#include <recGbl.h>
#include <alarm.h>
#include <errlog.h>
#include <dbDefs.h>
#include <dbAccess.h>
#include <epicsExport.h>
#include <epicsMutex.h>

#include <boRecord.h>
#include <biRecord.h>
#include <mbboRecord.h>
#include <mbbiRecord.h>
#include <iocsh.h>
#include "cp_config.h"
#include "XPort-i2c.h"

#define PCA9571_RD_ADDR		0x4B
#define PCA9571_WR_ADDR		0x4A

// mutex to guarantee exclusive access between thread for different timeperiod
epicsMutexId mutex = 0;

static long init_device(int phase);

// bo record

static long write_bo(boRecord *prec);

struct {

   long      number;
   DEVSUPFUN report;
   DEVSUPFUN init;
   DEVSUPFUN init_record;
   DEVSUPFUN get_ioint_info;
   DEVSUPFUN write_bo;

} devBoXPort = {

   5,
   NULL,
   init_device,
   NULL,
   NULL,
   write_bo
};

// bi record

static long read_bi(biRecord *prec);

struct {

   long      number;
   DEVSUPFUN report;
   DEVSUPFUN init;
   DEVSUPFUN init_record;
   DEVSUPFUN get_ioint_info;
   DEVSUPFUN read_bi;

} devBiXPort = {

   5,
   NULL,
   init_device,
   NULL,
   NULL,
   read_bi 
};

// mbbo record

static long init_i2cbus(int phase);
static long write_mbbo(mbboRecord *prec);

struct {

   long      number;
   DEVSUPFUN report;
   DEVSUPFUN init;
   DEVSUPFUN init_record;
   DEVSUPFUN get_ioint_info;
   DEVSUPFUN write_mbbo;

} devMbboXPort = {

   5,
   NULL,
   init_i2cbus,
   NULL,
   NULL,
   write_mbbo
};

// mbbi record

static long read_mbbi(mbbiRecord *prec);

struct {

   long      number;
   DEVSUPFUN report;
   DEVSUPFUN init;
   DEVSUPFUN init_record;
   DEVSUPFUN get_ioint_info;
   DEVSUPFUN read_mbbi;

} devMbbiXPort = {

   5,
   NULL,
   init_i2cbus,
   NULL,
   NULL,
   read_mbbi 
};

static long init_device(int phase) {

   if(phase == 0) {

      if(cp_config_init() == -1) {

         errlogPrintf("ERROR: CPM config failed\n");
         return(S_dev_noDevSup);
      }
   }

   return(0);
}

static long write_bo(boRecord *prec) {

   // set CP2 pin as output
   cp_config_type_set (2, 1);	

   // set CP2 value
   cp_config_data_output (2, prec->rval); 

   return(0);
}

static long read_bi(biRecord *prec) {

   int val;

   // read CP2 value
   cp_config_data_input(2, &val);

   prec->rval = val;
   
   return(0);
}

static long init_i2cbus(int phase) {


   if(phase == 0) { 

      if (!mutex)
         mutex = epicsMutexCreate();
      i2c_init();
   }

   return(0);
}

static long write_mbbo(mbboRecord *prec) {

   if(prec->rval == 0) {

      // software reset 
      epicsMutexLock(mutex);
         i2c_start();
         i2c_write_byte(0x00);
         i2c_write_byte(0x06);
         i2c_stop();
      epicsMutexUnlock(mutex);

   } else {

      epicsMutexLock(mutex);
         i2c_start();
         i2c_write_byte(PCA9571_WR_ADDR);
         i2c_write_byte(prec->rval);
         i2c_stop();
      epicsMutexUnlock(mutex);
   }

   return(0);
}

static long read_mbbi(mbbiRecord *prec) {

epicsMutexLock(mutex);
   i2c_start();
   i2c_write_byte(PCA9571_RD_ADDR);
   prec->rval = i2c_read_byte(ACK);
   i2c_stop();
epicsMutexUnlock(mutex);

   if(prec->rval == 255)
      prec->rval = 0;

   return(0);
}

epicsExportAddress(dset,devBoXPort);
epicsExportAddress(dset,devBiXPort);
epicsExportAddress(dset,devMbboXPort);
epicsExportAddress(dset,devMbbiXPort);
