#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <sys/ioctl.h>
#include <linux/ioctl.h>
#include <linux/spi/spidev.h>

#include "spi.h"

#define N_SAMPLES	50
#define SPREAD		1
#define scale     -600// calibration parameter

int main(void) {
	spi_t spi;
	spi_bit_order_t MSB_FIRST;
	uint8_t buf[1] = {0x00};
	uint8_t buf0[1];
	int8_t buf2[7];
	uint8_t buf1[7] = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x80}; // To change the gain to 64, change the last byte(0x80) to (0xA8) or 32 => (0xA0)
	char buffer [8];
	unsigned char byte;
	int32_t desired_bits;
	int i, j;
	int size = 6;
	int32_t offset;
	int nsamples=N_SAMPLES;
	long samples[nsamples];
	float spread_percent = SPREAD / 100.0 /2.0;
	float filter_low, filter_high;
	long tmp_avg=0;
	long tmp_avg2;

	
    /* Open spidev0.0 with mode 0 and max speed 1MHz */
    if (spi_open(&spi, "/dev/spidev0.0", 0, 1000000) < 0) {
        fprintf(stderr, "spi_open(): %s\n", spi_errmsg(&spi));
        exit(1);
    }
	
	/* Set_Offset */

	i=0;
	j=0;
		printf("Wait: Getting Tare\n");

		while(i<=nsamples)
		{	/* Shift out 1 byte of 0x00 and read DOUT */
		
			if (spi_transfer(&spi, buf, buf0, sizeof(buf)) < 0) 
			{
			        fprintf(stderr, "spi_transfer(): %s\n", spi_errmsg(&spi));
			        exit(1);
			}
		
			if(buf0[0] == 0x00)
			{
			spi_transfer(&spi, buf1, buf2, sizeof(buf2));
			desired_bits = get_bits(buf2);
			samples[i] = desired_bits;
			i++;
			}
		}
		
		for(i=0;i<nsamples;i++)
		{		
		tmp_avg += samples[i];
		}
	//usleep(6000);
  		

  tmp_avg = tmp_avg / nsamples;


  tmp_avg2 = 0;
  j=0;

  filter_low =  (float) tmp_avg * (1.0 - spread_percent);
  filter_high = (float) tmp_avg * (1.0 + spread_percent);

//  printf("%d %d\n", (int) filter_low, (int) filter_high);

  for(i=0;i<nsamples;i++) {
	if ((samples[i] < filter_high && samples[i] > filter_low) || 
            (samples[i] > filter_high && samples[i] < filter_low) ) {
		tmp_avg2 += samples[i];
	        j++;
	}
  }

  if (j == 0) {
    printf("No data to consider: Change the spread or the number of samples\n");
   exit(255);

  }


	offset = tmp_avg2/j;
	//offset = tmp_avg;	
	printf("Offset: %d\n", offset);
	printf("Starting...\n" );
usleep(5000000);
while(1)
{
	 
	/* Shift out 1 byte of 0x00 and read DOUT */
	if (spi_transfer(&spi, buf, buf0, sizeof(buf)) < 0) 
	{
	        fprintf(stderr, "spi_transfer(): %s\n", spi_errmsg(&spi));
	        exit(1);
	}
	/*If DOUT is 0x00, Shift out 4 bytes that represents 24 pulses + 1 of set gain(128)  */
	if(buf0[0] == 0x00){
		spi_transfer(&spi, buf1, buf2, sizeof(buf2));
		desired_bits = get_bits(buf2);
	}
	
	printf("Value: %d grams\n", (desired_bits - offset)/scale);

	
}
    spi_close(&spi);
    return 0;
}


/*function to bit bang the interface t*/
int32_t get_bits(uint8_t buf2[7])
{
 		unsigned char byte;		
		int32_t desired_bits;
 		int i, j;
    		int size = 6;
		desired_bits = 0;   
		for (i=0;i<=size-1;i++)
		{
	        	for (j=6;j>=0;j=j-2){
	            		byte = buf2[i] & (1<<j);
	            		byte >>= j;
	            		desired_bits = desired_bits | byte ;
	            		if (j>0 | i<size-1)
	            			desired_bits = (desired_bits<<1);
		        }
		}
	return desired_bits;
}


static int _spi_error(struct spi_handle *spi, int code, int c_errno, const char *fmt, ...) {
    va_list ap;

    spi->error.c_errno = c_errno;

    va_start(ap, fmt);
    vsnprintf(spi->error.errmsg, sizeof(spi->error.errmsg), fmt, ap);
    va_end(ap);

    /* Tack on strerror() and errno */
    if (c_errno) {
        char buf[64];
        strerror_r(c_errno, buf, sizeof(buf));
        snprintf(spi->error.errmsg+strlen(spi->error.errmsg), sizeof(spi->error.errmsg)-strlen(spi->error.errmsg), ": %s [errno %d]", buf, c_errno);
    }

    return code;
}

int spi_open(spi_t *spi, const char *path, unsigned int mode, uint32_t max_speed) {
    return spi_open_advanced(spi, path, mode, max_speed, MSB_FIRST, 8, 0);
}

int spi_open_advanced(spi_t *spi, const char *path, unsigned int mode, uint32_t max_speed, spi_bit_order_t bit_order, uint8_t bits_per_word, uint8_t extra_flags) {
    uint8_t data8;

    /* Validate arguments */
    if (mode & ~0x3)
        return _spi_error(spi, SPI_ERROR_ARG, 0, "Invalid mode (can be 0,1,2,3)");
    if (bit_order != MSB_FIRST && bit_order != LSB_FIRST)
        return _spi_error(spi, SPI_ERROR_ARG, 0, "Invalid bit order (can be MSB_FIRST,LSB_FIRST)");

    memset(spi, 0, sizeof(struct spi_handle));

    /* Open device */
    if ((spi->fd = open(path, O_RDWR)) < 0)
        return _spi_error(spi, SPI_ERROR_OPEN, errno, "Opening SPI device \"%s\"", path);

    /* Set mode, bit order, extra flags */
    data8 = mode | ((bit_order == LSB_FIRST) ? SPI_LSB_FIRST : 0) | extra_flags;
    if (ioctl(spi->fd, SPI_IOC_WR_MODE, &data8) < 0) {
        int errsv = errno;
        close(spi->fd);
        return _spi_error(spi, SPI_ERROR_CONFIGURE, errsv, "Setting SPI mode");
    }

    /* Set max speed */
    if (ioctl(spi->fd, SPI_IOC_WR_MAX_SPEED_HZ, &max_speed) < 0) {
        int errsv = errno;
        close(spi->fd);
        return _spi_error(spi, SPI_ERROR_CONFIGURE, errsv, "Setting SPI max speed");
    }

    /* Set bits per word */
    if (ioctl(spi->fd, SPI_IOC_WR_BITS_PER_WORD, &bits_per_word) < 0) {
        int errsv = errno;
        close(spi->fd);
        return _spi_error(spi, SPI_ERROR_CONFIGURE, errsv, "Setting SPI bits per word");
    }

    return 0;
}

int spi_transfer(spi_t *spi, const uint8_t *txbuf, uint8_t *rxbuf, size_t len) {
    struct spi_ioc_transfer spi_xfer;

    /* Prepare SPI transfer structure */
    memset(&spi_xfer, 0, sizeof(struct spi_ioc_transfer));
    spi_xfer.tx_buf = (__u64)txbuf;
    spi_xfer.rx_buf = (__u64)rxbuf;
    spi_xfer.len = len;
    spi_xfer.delay_usecs = 0;
    spi_xfer.speed_hz = 0;
    spi_xfer.bits_per_word = 0;
    spi_xfer.cs_change = 0;

    /* Transfer */
    if (ioctl(spi->fd, SPI_IOC_MESSAGE(1), &spi_xfer) < 1)
        return _spi_error(spi, SPI_ERROR_TRANSFER, errno, "SPI transfer");

    return 0;
}

int spi_close(spi_t *spi) {
    if (spi->fd < 0)
        return 0;

    /* Close fd */
    if (close(spi->fd) < 0)
        return _spi_error(spi, SPI_ERROR_CLOSE, errno, "Closing SPI device");

    spi->fd = -1;

    return 0;
}

int spi_get_mode(spi_t *spi, unsigned int *mode) {
    uint8_t data8;

    if (ioctl(spi->fd, SPI_IOC_RD_MODE, &data8) < 0)
        return _spi_error(spi, SPI_ERROR_QUERY, errno, "Getting SPI mode");

    *mode = data8 & (SPI_CPHA | SPI_CPOL);

    return 0;
}

int spi_get_max_speed(spi_t *spi, uint32_t *max_speed) {
    uint32_t data32;

    if (ioctl(spi->fd, SPI_IOC_RD_MAX_SPEED_HZ, &data32) < 0)
        return _spi_error(spi, SPI_ERROR_QUERY, errno, "Getting SPI max speed");

    *max_speed = data32;

    return 0;
}

int spi_get_bit_order(spi_t *spi, spi_bit_order_t *bit_order) {
    uint8_t data8;

    if (ioctl(spi->fd, SPI_IOC_RD_LSB_FIRST, &data8) < 0)
        return _spi_error(spi, SPI_ERROR_QUERY, errno, "Getting SPI bit order");

    if (data8)
        *bit_order = LSB_FIRST;
    else
        *bit_order = MSB_FIRST;

    return 0;
}

int spi_get_bits_per_word(spi_t *spi, uint8_t *bits_per_word) {
    uint8_t data8;

    if (ioctl(spi->fd, SPI_IOC_RD_BITS_PER_WORD, &data8) < 0)
        return _spi_error(spi, SPI_ERROR_QUERY, errno, "Getting SPI bits per word");

    *bits_per_word = data8;

    return 0;
}

int spi_get_extra_flags(spi_t *spi, uint8_t *extra_flags) {
    uint8_t data8;

    if (ioctl(spi->fd, SPI_IOC_RD_MODE, &data8) < 0)
        return _spi_error(spi, SPI_ERROR_QUERY, errno, "Getting SPI mode flags");

    /* Extra mode flags without mode 0-3 and bit order */
    *extra_flags = data8 & ~( SPI_CPOL | SPI_CPHA | SPI_LSB_FIRST );

    return 0;
}

int spi_set_mode(spi_t *spi, unsigned int mode) {
    uint8_t data8;

    if (mode & ~0x3)
        return _spi_error(spi, SPI_ERROR_ARG, 0, "Invalid mode (can be 0,1,2,3)");

    if (ioctl(spi->fd, SPI_IOC_RD_MODE, &data8) < 0)
        return _spi_error(spi, SPI_ERROR_QUERY, errno, "Getting SPI mode");

    data8 &= ~(SPI_CPOL | SPI_CPHA);
    data8 |= mode;

    if (ioctl(spi->fd, SPI_IOC_WR_MODE, &data8) < 0)
        return _spi_error(spi, SPI_ERROR_CONFIGURE, errno, "Setting SPI mode");

    return 0;
}

int spi_set_bit_order(spi_t *spi, spi_bit_order_t bit_order) {
    uint8_t data8;

    if (bit_order != MSB_FIRST && bit_order != LSB_FIRST)
        return _spi_error(spi, SPI_ERROR_ARG, 0, "Invalid bit order (can be MSB_FIRST,LSB_FIRST)");

    if (bit_order == LSB_FIRST)
        data8 = 1;
    else
        data8 = 0;

    if (ioctl(spi->fd, SPI_IOC_WR_LSB_FIRST, &data8) < 0)
        return _spi_error(spi, SPI_ERROR_CONFIGURE, errno, "Setting SPI bit order");

    return 0;
}

int spi_set_extra_flags(spi_t *spi, uint8_t extra_flags) {
    uint8_t data8;

    if (ioctl(spi->fd, SPI_IOC_RD_MODE, &data8) < 0)
        return _spi_error(spi, SPI_ERROR_QUERY, errno, "Getting SPI mode flags");

    /* Keep mode 0-3 and bit order */
    data8 &= (SPI_CPOL | SPI_CPHA | SPI_LSB_FIRST);
    /* Set extra flags */
    data8 |= extra_flags;

    if (ioctl(spi->fd, SPI_IOC_WR_MODE, &data8) < 0)
        return _spi_error(spi, SPI_ERROR_CONFIGURE, errno, "Setting SPI mode flags");

    return 0;
}

int spi_set_max_speed(spi_t *spi, uint32_t max_speed) {

    if (ioctl(spi->fd, SPI_IOC_WR_MAX_SPEED_HZ, &max_speed) < 0)
        return _spi_error(spi, SPI_ERROR_CONFIGURE, errno, "Setting SPI max speed");

    return 0;
}

int spi_set_bits_per_word(spi_t *spi, uint8_t bits_per_word) {

    if (ioctl(spi->fd, SPI_IOC_WR_BITS_PER_WORD, &bits_per_word) < 0)
        return _spi_error(spi, SPI_ERROR_CONFIGURE, errno, "Setting SPI bits per word");

    return 0;
}

int spi_tostring(spi_t *spi, char *str, size_t len) {
    unsigned int mode;
    char mode_str[2];
    uint32_t max_speed;
    char max_speed_str[16];
    uint8_t bits_per_word;
    char bits_per_word_str[2];
    spi_bit_order_t bit_order;
    char bit_order_str[16];
    uint8_t extra_flags;
    char extra_flags_str[4];

    if (spi_get_mode(spi, &mode) < 0)
        strncpy(mode_str, "?", sizeof(mode_str));
    else
        snprintf(mode_str, sizeof(mode_str), "%d", mode);

    if (spi_get_max_speed(spi, &max_speed) < 0)
        strncpy(max_speed_str, "?", sizeof(max_speed_str));
    else
        snprintf(max_speed_str, sizeof(max_speed_str), "%u", max_speed);

    if (spi_get_bit_order(spi, &bit_order) < 0)
        strncpy(bit_order_str, "?", sizeof(bit_order_str));
    else
        strncpy(bit_order_str, (bit_order == LSB_FIRST) ? "LSB first" : "MSB first", sizeof(bit_order_str));

    if (spi_get_bits_per_word(spi, &bits_per_word) < 0)
        strncpy(bits_per_word_str, "?", sizeof(bits_per_word_str));
    else
        snprintf(bits_per_word_str, sizeof(bits_per_word_str), "%u", bits_per_word);

    if (spi_get_extra_flags(spi, &extra_flags) < 0)
        strncpy(extra_flags_str, "?", sizeof(extra_flags_str));
    else
        snprintf(extra_flags_str, sizeof(extra_flags_str), "%02x", extra_flags);

    return snprintf(str, len, "SPI (fd=%d, mode=%s, max_speed=%s, bit_order=%s, bits_per_word=%s, extra_flags=%s)", spi->fd, mode_str, max_speed_str, bit_order_str, bits_per_word_str, extra_flags_str);
}

const char *spi_errmsg(spi_t *spi) {
    return spi->error.errmsg;
}

int spi_errno(spi_t *spi) {
    return spi->error.c_errno;
}

int spi_fd(spi_t *spi) {
    return spi->fd;
}
