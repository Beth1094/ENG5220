#ifndef HX711_H
    #define HX711_H
     
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <linux/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <stddef.h>
#include <stdarg.h>

 
 
class HX711{
 
public:
    HX711(); //default constructor 
    HX711(std::string devspi, unsigned char spiMode, unsigned int spiSpeed, unsigned char spibitsPerWord);
    ~HX711();
    int spiTransfer(const uint8_t *txbuf, uint8_t *rxbuf, size_t len);
     
private:
    unsigned char mode; //defines the SPI mode used: SPI_MODE_0
    unsigned char bitsPerWord; //defines the bit width of the data transmitted.This is normally 8.
    unsigned int speed; //Bus speed or SPI clock frequency: it can be only 0.5, 1, 2, 4, 8, 16, 32 MHz.
    int spifd; //file descriptor of spi device
     
    int spiOpen(std::string devspi);
    int spiClose();
     
};
 
#endif