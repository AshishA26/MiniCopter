# MiniCopter
A mini quadcopter that is lightweight (~100g) and designed for agility. It is made using an Arduino Nano, an MPU6050 for orientation sensing, an NRF24L01 for wireless communication, MOSFETs that act as motor drivers, and 8520 motors. The quadcopter is controlled using a custom transmitter that has 2 joysticks and an NRF24L01. In addition, I created a custom PCB to house all these components and allow for better wiring, testing, and weight reduction.

Programmed in `Arduino IDE`, models created in `Autodesk Inventor`, schematics and PCB created in `KiCad`.

![CopterPic11](./Images/CopterPic11.jpg)
![CopterGif1](./Images/CopterGif1.gif)

Demo showing the tilt-based motor control of the quadcopter that allows for the quadcopter to stabilize and balance ([full video](https://www.youtube.com/watch?v=k4_8MwJ_Zw4)):
![CopterGif2](./Images/CopterGif2.gif)

## PCB Design
My original design used a perfboard, but I eventually designed a PCB that would not only simplify debugging and wire routing, but also allow for some weight reduction. The PCB takes into account many things such as the current that will flow from the LiPo batteries, the size of all the components, and more.

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
The main chassis has been built such that the frame is strong and firm enough, while reducing weight.
![CopterPic4](./Images/CopterPic4.jpg)
![CopterPic12](./Images/CopterPic12.jpg)
The propellor gaurds have also been designed such that it protects people and the quadcopter, while also being very lightweight.
![CopterPic13](./Images/CopterPic13.jpg)

## Other Tests

Checkout some [flight testing](https://www.youtube.com/watch?v=XLUD_ImCz4A).

Checkout a demo of [the joystick wirelessly controlling a motor](https://www.youtube.com/watch?v=rh6yMr4QYGM).

To determine the strenght of each motor (how much each would be able to lift up), I 3D printed some parts and flipped the motor upside down:

![CopterPic13](./Images/Test1.jpg)

## Setup
- To open the schematics and pcb, install my [KiCAD libraries](https://github.com/AbhinavA10/kicad-libraries).