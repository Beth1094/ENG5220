# Research Links for the Hydration-Station Project

## Setting Up Raspberry Pi
* Format SD card and put Raspbian Desktop on it: https://www.raspberrypi.org/downloads/raspbian/ 
* Check g++ compiler, cmake and WiringPi are installed on Pi and run a basic C++ program on the Pi: https://nickcullen.net/blog/raspberry-pi-tutorials/raspberry-pi-c-the-beginnings/ 
* Information about WiringPi, examples and how to access GPIO pins: http://wiringpi.com/
* GPIO pin numbering (note: GPIO pin 17 corresponds to WiringPi pin 0. It is the WiringPi pin number that is referenced in the C++ code and the physical hardware must be connected to the corresponding GPIO pin on the Pi): http://wiringpi.com/pins/

## Hardware

### Additional Links on Accessing Pi's GPIOs
* Introduction to accessing the Raspberry Pi's GPIO in C++ (sysfs) - alternative to using WiringPi (sysfs mentioned in lectures):  http://www.hertaville.com/introduction-to-accessing-the-raspberry-pis-gpio-in-c.html

### Deploying Code onto Raspberry Pi
* Deploy code from visual studio on laptop to RPi: https://www.youtube.com/watch?v=_IpjihBU3ps  

### Components
* Load cells: https://www.amazon.co.uk/Cylewet-Half-bridge-Weighing-Electric-Resistance/dp/B06XFHQK59/ref=pd_ybh_a_1?_encoding=UTF8&psc=1&refRID=7X8E7V7C0WGQV6M0Q0MR x2  
* Water dispenser: https://www.amazon.co.uk/d/Home-Kitchen/Large-Plastic-Dispenser-Cocktails-Beverages/B01J03V0WO/ref=sr_1_4?ie=UTF8&qid=1548864212&sr=8-4&keywords=3+litre+water+dispenser 
* HX711 pressure sensor: https://www.amazon.co.uk/HALJIA-Weighing-Pressure-Dual-channel-Precision/dp/B01MZBBIO2/ref=sr_1_2?ie=UTF8&qid=1548865409&sr=8-2&keywords=hx711 

### Building Weighing Scales & electronics wiring 
* http://grahamtech.azurewebsites.net/digital-scale-hack/ 
* https://tutorials-raspberrypi.com/digital-raspberry-pi-scale-weight-sensor-hx711/ 
* https://www.instructables.com/id/How-to-Build-Arduino-Weighing-Scales/ 
* Diagrams of load cell wiring:  https://www.amazon.co.uk/Weighting-Half-bridge-Amplifier-Bathroom-Arduino/dp/B07FMN1DBN/ref=pd_sbs_23_6/257-1380011-8269453?_encoding=UTF8&pd_rd_i=B07FMN1DBN&pd_rd_r=2f39e573-263b-11e9-b4ec-933b86c55cbe&pd_rd_w=fcncM&pd_rd_wg=dkIxw&pf_rd_p=18edf98b-139a-41ee-bb40-d725dd59d1d3&pf_rd_r=8PP2633MYYWFC86ZZ5BR&psc=1&refRID=8PP2633MYYWFC86ZZ5BR  


### The HX711 Amplifier
The following links provide information on how the HX711 amplifier works and how the Raspberry Pi can communicate with it
* HX711 datasheet:  https://cdn.sparkfun.com/datasheets/Sensors/ForceFlex/hx711_english.pdf 
* Forum about HX711 interface: https://forum.arduino.cc/index.php?topic=418170.0 
* Tutorial to Interface HX711 for Arduino:  https://www.instructables.com/id/How-to-Interface-HX711-Balance-Module-With-Load-Ce/
* HX711 communication C/C++ code: 
  ** https://github.com/PeakUp/HX711-Load-Cell-Amplifier-Static-Library
  ** https://stackoverflow.com/questions/44720199/android-things-hx711
  ** https://github.com/georgeredinger/hx711-1
  ** https://github.com/gandalf15/HX711/tree/master/HX711_C
  ** https://github.com/ggurov/hx711
