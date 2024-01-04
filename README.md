# MiniCopter
A mini quadcopter that is lightweight (~100g) and designed for agility. It is made using an Arduino Nano, an MPU6050 for orientation sensing, an NRF24L01 for wireless communication, MOSFETs that act as motor drivers, and 8520 motors. The quadcopter is controlled using a custom transmitter that has 2 joysticks and an NRF24L01, and uses PID motor control for stabilizing roll and pitch of the quadcopter. In addition, I created a custom PCB to house all these components and allow for better wiring, testing, and weight reduction.

Programmed in `Arduino IDE`, models created in `Autodesk Inventor`, schematics and PCB created in `KiCad`.

![CopterPic11](./Images/CopterPic11.jpg)
![CopterGif1](./Images/CopterGif1.gif)

Demo showing the PID motor control of the quadcopter that allows for the quadcopter to stabilize and balance ([full video](https://www.youtube.com/watch?v=k4_8MwJ_Zw4)):
![CopterGif2](./Images/CopterGif2.gif)

## PCB Design
My original design used a perfboard, but I eventually designed a 2-layer PCB that would not only simplify debugging and wire routing, but also allow for some weight reduction. 

The PCB contains all circuitry and the connections between them. The placement, orientation, and connections of each component was carefully considered when making decisions on the design of the PCB. The size of the PCB itself was also an important factor for me to consider because I needed to be the smallest and most optimal size it could be in order to reduce the weight on the quadcopter.

The PCB also acts as custom motor drivers for each motor by employing the use of MOSFETs, as normal Arduino motor drivers available online are too large and are not meant for high current flow and high speeds. 

Through calculations, I determined the trace size required for each component on the board, such as the LiPo battery connections needing thicker traces due to the high current. After various tests, it was found that dupont connectors could not be used to transfer current to the motors as the end connectors had resistance, so having a PCB with custom trace sizes was very useful.

Additionally, through testing on the Perfboard, I found that 2 LiPo batteries were required as I not only needed to power the 4 motors, but also the Arduino (which also powers other components).

![PCB_Pic8](./Images/PCB_Pic8.jpg)
![PCB_Pic9](./Images/PCB_Pic9.jpg)
![PCB_Pic7](./Images/PCB_Pic7.png)

### Routing
![PCB_Pic1](./Images/PCB_Pic1.png)
![PCB_Pic2](./Images/PCB_Pic2.png)
![PCB_Pic3](./Images/PCB_Pic3.png)

### Original Perfboard Design

| Perfboard Front Side | Perfboard Back Side |
| :---: | :---: |
| ![CopterPic1](./Images/CopterPic1.jpg)  | ![CopterPic2](./Images/CopterPic2.jpg) |
| Back side of complete perfboard | Perfboard on minicoptoper |
| ![CopterPic9](./Images/CopterPic9.jpg)  | ![CopterPic0](./Images/CopterPic0.jpg) |

## Schematics
![CopterSchematic](./Schematics/MiniCopterSchematic/MiniCopterSchematic.svg)
![CopterSchematic](./Schematics/MiniCopterTransmitterSchematic/MiniCopterTransmitterSchematic.svg)

## Part Pictures
After many tests and designs, the final chassis has been built such that the frame is strong and firm enough, while greatly reducing weight. The propellor gaurds have also been iteratively designed after numerous tests such that it protects people and the quadcopter, while also being very lightweight.

![CopterPic4](./Images/CopterPic4.jpg)
![CopterPic12](./Images/CopterPic12.jpg)
![CopterPic13](./Images/CopterPic13.jpg)

## Other Tests

Checkout some [flight testing](https://www.youtube.com/watch?v=XLUD_ImCz4A).

Checkout a demo of [the joystick wirelessly controlling a motor](https://www.youtube.com/watch?v=rh6yMr4QYGM).

To determine the strength of each motor, I 3D printed some parts and flipped the motor upside down to conduct a thrust analysis. This allowed me to see if the MOSFETs and batteries would be able to supply enough current to the motors.

![CopterPic13](./Images/Test1.jpg)



## Setup
- To open the schematics and pcb, install my [KiCAD libraries](https://github.com/AbhinavA10/kicad-libraries).
