TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = XPort
# XPort.dbd will be created and installed
DBD += XPort.dbd

# XPort.dbd will be made up from these files:
XPort_DBD += base.dbd

# Include dbd files from all support applications:
XPort_DBD += XPortdev.dbd

# Add all the support libraries needed by this IOC
XPort_LIBS += cp

# XPort_registerRecordDeviceDriver.cpp derives from XPort.dbd
XPort_SRCS += XPort_registerRecordDeviceDriver.cpp
XPort_SRCS += devXPort.c
XPort_SRCS += XPort-i2c.c

# Build the main IOC entry point on workstation OSs.
XPort_SRCS_DEFAULT += XPortMain.cpp
XPort_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#XPort_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
XPort_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

