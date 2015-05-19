#!../../bin/uclinux-lantronix/XPort

#< envPaths

## Register all support components
dbLoadDatabase("./XPort.dbd",0,0)
XPort_registerRecordDeviceDriver(pdbbase) 

## Load record instances
dbLoadRecords("./XPort.db","H=usop05,D=Lantronix XPort")

iocInit()

