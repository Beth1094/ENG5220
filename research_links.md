# Research Links for the Hydration-Station Project

## Setting Up Raspberry Pi
* Format SD card and put Raspbian Desktop on it: https://www.raspberrypi.org/downloads/raspbian/ 
* Check g++ compiler, cmake and WiringPi are installed on Pi and run a basic C++ program on the Pi: https://nickcullen.net/blog/raspberry-pi-tutorials/raspberry-pi-c-the-beginnings/ 
* Information about WiringPi, examples and how to access GPIO pins: http://wiringpi.com/
* GPIO pin numbering (note: GPIO pin 17 corresponds to WiringPi pin 0. It is the WiringPi pin number that is referenced in the C++ code and the physical hardware must be connected to the corresponding GPIO pin on the Pi): http://wiringpi.com/pins/

## Aside on C++ Programming and Syntax
These links are just for reference.
* https://www.youtube.com/user/BoQianTheProgrammer/playlists 
* https://www.tutorialspoint.com/cplusplus/

## Additional Links on Accessing Pi's GPIOs
* Introduction to accessing the Raspberry Pi's GPIO in C++ (sysfs) - alternative to using WiringPi (sysfs mentioned in lectures):  http://www.hertaville.com/introduction-to-accessing-the-raspberry-pis-gpio-in-c.html

## Deploying Code onto Raspberry Pi
* Deploy code from visual studio on laptop to RPi: https://www.youtube.com/watch?v=_IpjihBU3ps  

## Hardware
* Full-bridge strain gauge theory: https://www.allaboutcircuits.com/textbook/direct-current/chpt-9/strain-gauges/
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
  * https://github.com/PeakUp/HX711-Load-Cell-Amplifier-Static-Library
  * https://stackoverflow.com/questions/44720199/android-things-hx711
  * https://github.com/georgeredinger/hx711-1
  * https://github.com/gandalf15/HX711/tree/master/HX711_C
  * https://github.com/ggurov/hx711
  
 ### Raspberry Pi controlled hose pipe
 * http://danshose.blogspot.com/
 * Circuitry for controlling a solenoid valve from an arduino. Will also work for Pi (could use for a simple PCB): http://www.martyncurrey.com/controlling-a-solenoid-valve-from-an-arduino/
 * https://www.youtube.com/watch?v=ofzjzf_rhZc
 * How to connect solenoid valve: https://www.youtube.com/watch?v=_tby5VuvNuk 
 #### Components
 * 12V DC solenoid valve from Amazon: https://www.amazon.co.uk/Electric-Solenoid-Valve-Water-Air/dp/B00BVESSJY/ref=pd_cp_60_1/257-1380011-8269453?_encoding=UTF8&pd_rd_i=B00BVESSJY&pd_rd_r=e7540840-3ed9-11e9-9214-cfe8ba298bf3&pd_rd_w=Ui5bp&pd_rd_wg=5WUaG&pf_rd_p=01704ebe-a86a-4b47-8c36-0f9f5bbc2882&pf_rd_r=K9Y10ZG1MBV4E1HPJKR8&psc=1&refRID=K9Y10ZG1MBV4E1HPJKR8
 * 1/2 inch Hose connector: https://www.amazon.co.uk/Draper-Expert-Garden-Connector-2-Inch/dp/B01089HKJ6/ref=pd_vtph_lp_tr_t_2/257-1380011-8269453?_encoding=UTF8&pd_rd_i=B01089HKJ6&pd_rd_r=fe5e0323-3ed9-11e9-8a7d-e7ec3eadf0c5&pd_rd_w=kAV5e&pd_rd_wg=TwCXF&pf_rd_p=eb02db1b-a172-4b0e-887c-299e5e502bb0&pf_rd_r=CYTN06AHJ19GWN8HYZQE&psc=1&refRID=CYTN06AHJ19GWN8HYZQE
 * 1/2 inch hose connection set: https://www.amazon.co.uk/Silverline-353266-Hose-Connection-Set/dp/B004P3OUUY/ref=sr_1_4?s=diy&ie=UTF8&qid=1551744935&sr=1-4&keywords=1%2F2+hose+pipe+short
 * TIP120 transistor
 * 1N4007 diode
 * 2.2 Kohm resistor
 * 12V battery 

### PCB design software
* https://www.expresspcb.com/

## Client-Server Communication
This section contains links with information about how to set up a client-server with Sockets. The Pi will act as the server and the windows pc as the client. In this way the Pi can send the information it collects to a lightweight remote client. 
* Useful description of client-server implementation in C/C++ (second link contains code example and description of Sockets): https://www.raspberrypi.org/forums/viewtopic.php?t=57897, https://www.thegeekstuff.com/2011/12/c-socket-programming/
* Websockets and webserver alternative for a web application rather than a local application: https://raspberrypi.stackexchange.com/questions/47467/what-is-the-best-way-to-send-data-from-raspilinux-to-laptopwindows-in-realti/48125

### Control GIPO pins with webpage using node.js and websockets
* https://www.w3schools.com/nodejs/nodejs_raspberrypi_blinking_led.asp
* https://www.w3schools.com/nodejs/nodejs_raspberrypi_webserver_websocket.asp?fbclid=IwAR34ycTn4GDGx6LVIBwSPDeNtodkVesYtefKqH4x77nBTOofGSNyA8rX7KM
* Javascript authentication: https://www.formget.com/javascript-login-form/?fbclid=IwAR39zhLEFXxUOe_7WDLhbqZSka517_KwuENBo8frN_vTHITgJPHtXdRJoVE
* HTML: https://www.w3schools.com/html/default.asp?fbclid=IwAR0CxmJZnXJmnqVeaqhyrNRx790FVXvouGesxjFb9x9pv9LIvRCutS48k7o 
* Streaming data from C++ to Node.js: https://nodeaddons.com/streaming-data-from-c-to-node-js/

## GUI Implementation
This section contains links with information about how to set up a GUI. The GUI needs to be able to display the data received by the client in a user-friendly manner (note this is not required if using a web application instead - see above section).
* PyQT - writing a GUI in Python: https://www.tutorialspoint.com/pyqt/pyqt_hello_world.htm
* some other Python GUI stuff: https://learn.sparkfun.com/tutorials/python-gui-guide-introduction-to-tkinter/all 
* Arduino example of code which checks if client recieved data and displays it in GUI: http://forum.arduino.cc/index.php?topic=271097.0
