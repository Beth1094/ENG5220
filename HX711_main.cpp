#include "HX711.h"
using namespace std;


#define N_SAMPLES	100
#define SPREAD		1
#define scale     -142// calibration parameter

int32_t get_bits(uint8_t* dat); //forward ref function get_bits


int main(void) {
	uint8_t buf[1] = {0x00};
	uint8_t buf0[1];
	uint8_t buf2[7];
	uint8_t buf1[7] = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x80}; // To change the gain to 64, change the last byte(0x80) to (0xA8) or 32 => (0xA0)
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
     HX711 a2d("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);

	
	/* Set_Offset */

	i=0;
	j=0;
		printf("Wait: Getting Tare\n");

		while(i<=nsamples)
		{	/* Shift out 1 byte of 0x00 and read DOUT */
		
			if (a2d.spiTransfer(buf, buf0, sizeof(buf)) < 0) 
			{
			        perror("Could not transfer data");
			        exit(1);
			}
		
			if(buf0[0] == 0x00)
			{
			    a2d.spiTransfer(buf1, buf2, sizeof(buf2));
			    desired_bits = get_bits(buf2);
			    samples[i] = desired_bits;
			    i++;
			}
		}
		
		for(i=0;i<nsamples;i++)
		{		
		    tmp_avg += samples[i];
		}
  		

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
	if (a2d.spiTransfer(buf, buf0, sizeof(buf)) < 0) 
	{
	        perror("Could not transfer data");
	        exit(1);
	}
	/*If DOUT is 0x00, Shift out 4 bytes that represents 24 pulses + 1 of set gain(128)  */
	if(buf0[0] == 0x00){
		a2d.spiTransfer(buf1, buf2, sizeof(buf2));
		desired_bits = get_bits(buf2);
	}
	
	printf("Value: %d grams\n", (desired_bits - offset)/scale);
    //usleep(100000);
	
}
    a2d.~HX711();  //call destructor to close spi device 
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