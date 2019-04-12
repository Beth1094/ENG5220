## Hydration Station Documentation

## Hardware 









## Software 
The HX711 class gets weight values from the data pin from the HX711 SPI ADC with scaling and taring. The tare value is not scaled, but in raw A/D units. The SPI pins: SCK pin (clock pin MOSI/pin 19 on Raspberry) and the DOUT pin (data pin MISO/pin 21 on Raspberry), were used to retrieve data from the HX711 ADC as well as input selection (here SPI mode 0 was used), gain selection of the programmable gain amplifier and to control power down. The Raspberry pi was used to control the clock signal on the MOSI pin and a range of possible SPI bus speeds or SPI clock frequencies are possible for SPI devices: 0.5, 1, 2, 4, 8, 16, 32 MHz. 


When the Pi holds the clockPin high for greater than 60 ms, the HX711 goes into low power mode, holding the dataPin high. When the Pi sets the dataPin low, the HX711 wakes up, but does not have new data ready until 0.5 seconds after turning on. 
	
When output data are not ready for retrieval, digital output pin DOUT is high. With clock pin held low, (not reading any data) data pin pulses are 100 usec, frequency is 11.2 Hz (90 msec spacing) each high-to-low transution indicates a new value is available from the HX711
	
The data pin goes high when data has been read, and only goes low when new data is available

By applying 25~27 positive clock pulses at the clock pin, data is shifted out from the data output pin. Each clock pulse shifts out one bit, starting with the MSB bit first, until all 24 bits are shifted out. The 25th pulse at clock input will pull data pin back to high. Input and gain selection is controlled by adding a number of extra input clock pulses to the train after the data is collected.
	clock Pulses   	Input channel   Gain
	25               		A              	128
	26               		B              	32
	27               		A              	64
This code always runs the HX711 with high gain, input channel A, by using 25 pulses but this is easily chanheable within the code. This maps onto a pulsedThread train with 25 pulses with 1 us delay and duration time.
		
Data is 24 bit two's-complement differential signal min value is -8388608, max value is 8388607.
