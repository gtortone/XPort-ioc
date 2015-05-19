# XPort-ioc
Lantronix XPort IOC for uSOP

to compile IOC for XPort arch:

cd XPortApp/src
make -C O.uclinux-lantronix -f ../Makefile TOP=../../.. T_A=uclinux-lantronix
