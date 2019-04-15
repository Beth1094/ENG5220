# PCB Design

Designing the PCB has taken a few iterations throughout the course of the project.

## HX711 PCB

Template files available on Eagle were used to design the PCB for the HX711 ADC, this circuit was used to test the HX711 with the 
code for the scales. It reads out the information from the load cells and outputs the data to the command terminal on the raspberry pi.

Below shows a picture of the first attempt at designing and soldering the PCB, due to difficulties soldering related to the size of the surface mount resistors, capacitors and the drill holes the HX711 circuit was resized when integrating the ADC and the solenoid circuit together.

![HX711 Process](https://github.com/Beth1094/Hydration_Station/blob/master/PCB/HX711_ver1.jpg)

## Solenoid PCB

As can be seen in the photo below the first version of the solenoid PCB was too large, revisions were made to make it a more reasonable size when designing the integrated circuit, but this version was used to test the circuitry.

![SolenoidCircuit](https://github.com/Beth1094/Hydration_Station/blob/master/PCB/Solenoid_Circuit_ver_1.jpg)

## Integrated PCB

###### PCB Circuit Schematic and Board Layout

![Schematic](https://github.com/Beth1094/Hydration_Station/blob/master/PCB/PCB_schematic.PNG)

![Board](https://github.com/Beth1094/Hydration_Station/blob/master/PCB/PCB_board.PNG)

Below is the final version of our PCB (after many attempts!). It has wider spacing of the surface mount components to allow for easier soldeing and the pin headers are spaced accordingly so that the wire connections to the raspberry pi are easily accessed.

![IntegratedPCB](https://github.com/Beth1094/Hydration_Station/blob/master/PCB/integrated_PCB_!.jpg)

Unfortunately the HX711 PCB does not work correctly. In the process of making the PCB we had to desolder the HX711 SMD from an existing HX711 chip and resolder onto our board. We believe this process has 'fried' the SMD, however we now have the scale running on a pre-made HX711 chip.
