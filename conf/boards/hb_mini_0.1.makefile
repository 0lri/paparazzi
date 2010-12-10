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
GPS_UART_NR	= 0
GPS_BAUD	= B38400
GPS_LED     = 2
MODEM_UART_NR	= 1
MODEM_BAUD 	= B57600


#olri ADC_IR_TOP = ADC_0
#olri ADC_IR1 = ADC_1
#olri ADC_IR2 = ADC_2
#olri ADC_IR_NB_SAMPLES = 16
#olri ADC_GYRO_ROLL = ADC_3
#olri ADC_GYRO_PITCH = ADC_4
#olri ADC_GYRO_NB_SAMPLES = 16

#olri ADC_GENERIC_NB_SAMPLES = 16

# All targets on the TINY board run on the same processor achitecture
$(TARGET).ARCHDIR = $(ARCH)
