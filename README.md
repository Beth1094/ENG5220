## Hydration Station Documentation
Designed with industry/office use in mind, Hydration Station provides a way for employees to stay hydrated throughout their office hours allowing them to maintain alertness and concentration. Hydration Station allows the average water consupmtion per day to be monitored, encouraging employees to increase their water intake per day. Additional features; automatic replenishment when liquid level drops below a threshold level. 

Components required:
* Raspberry Pi 3 B+
* PCB (See PCB section for full component list)
* Load cell
* Load cell mount, i.e. chipboard or strong plastic sheeting
* Water bottle with a tap
* Funnel or hose


## Hardware 









## Software 
The HX711 class gets weight values from the data pin from the HX711 SPI ADC with scaling and taring. The tare value is not scaled, but in raw A/D units. The SPI pins: SCK pin (clock pin MOSI data line/pin 19 on Raspberry) and the DOUT pin (data pin MISO/pin 21 on Raspberry), were used to retrieve data from the HX711 ADC as well as input selection (here SPI mode 0 was used), gain selection of the programmable gain amplifier and to control power down. The Raspberry pi was used to control the clock signal on the MOSI pin and a range of possible SPI bus speeds or SPI clock frequencies are possible for SPI devices: 0.5, 1, 2, 4, 8, 16, 32 MHz. 


When the Pi holds the clockPin high for greater than 60 ms, the HX711 goes into low power mode, holding the dataPin high. When the Pi sets the dataPin low, the HX711 wakes up, but does not have new data ready until 0.5 seconds after turning on. 
	
When output data are not ready for retrieval, digital output pin DOUT is high. With clock pin held low, (not reading any data) data pin pulses are 100 usec, frequency is 11.2 Hz (90 msec spacing) each high-to-low transution indicates a new value is available from the HX711
	
The data pin goes high when data has been read, and only goes low when new data is available

By applying 25-27 positive clock pulses at the clock pin, data is shifted out from the data output pin. Each clock pulse shifts out one bit, starting with the MSB bit first, until all 24 bits are shifted out. The 25th pulse at clock input will pull data pin back to high. Input and gain selection is controlled by adding a number of extra input clock pulses to the train after the data is collected.

| CLock Pulses | Input Channel | Gain |
| --- | --- | --- | 
|25|A|128|
|26|B|32|
|27|A|64|

The HX711 interface needs at least 25 clock pulses, but the SPI hardware is only capable of increments of 8-bits so the function get_bits was written to bit-bang the interface. The MOSI data line was used to generate a clock pulse by writing the value “0xAA”, which will go high 4 times each byte, so 6 bytes were needed to achieve 24 pulses. Then one byte is sent to set the gain of the programmable amplifier: (0x80) for 124, (0xA8) for 64 and (0xA0) for 32.

The current set up of the code always runs the HX711 with high gain, input channel A, by using 25 pulses but this is easily changeable within the code. This maps onto a pulsedThread train with 25 pulses with 1 us delay and duration time.
		
Data is 24 bit two's-complement differential signal min value is -8388608, max value is 8388607.
