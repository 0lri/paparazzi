#
# hb_mini_0.1.makefile
#
# http://paparazzi.enac.fr/wiki/HB_MINI
#

ARCH=lpc21

BOARD=hb_mini
BOARD_VERSION=0.1

BOARD_CFG=\"boards/$(BOARD)_$(BOARD_VERSION).h\"

ifndef FLASH_MODE
FLASH_MODE = IAP
endif


LPC21ISP_BAUD = 38400
LPC21ISP_XTAL = 12000


### default settings for tiny_2 and twog
GPS_UART_NR	= 1
GPS_BAUD	= B38400
GPS_LED		= 2
MODEM_UART_NR	= 0
MODEM_BAUD	= B38400

# All targets on the TINY board run on the same processor achitecture
$(TARGET).ARCHDIR = $(ARCH)
