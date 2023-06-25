# MiniCopter
A mini quadcopter that is lightweight (~100g) and designed for agility. It is made using an Arduino Nano, an MPU6050 for orientation sensing, an NRF24L01 for wireless communication, MOSFETs that act as motor drivers, and 8520 motors. The quadcopter is controlled using a custom transmitter that has 2 joysticks and an NRF24L01.

Programmed in `Arduino IDE`, models created in `Autodesk Inventor`, schematics created in `KiCad`.

![CopterPic5](./Images/CopterPic0.jpg)

- More updates to come!

## Schematics
![CopterSchematic](./Schematics/MiniCopterSchematic/MiniCopterSchematic.svg)
![CopterSchematic](./Schematics/MiniCopterTransmitterSchematic/MiniCopterTransmitterSchematic.svg)

### Setup
- Install my [KiCAD libraries](https://github.com/AbhinavA10/kicad-libraries).

## Other Pictures
Unassembled 3D-printed parts:
![CopterPic4](./Images/CopterPic4.jpg)

Custom made perfboard:
![CopterPic1](./Images/CopterPic1.jpg)
![CopterPic2](./Images/CopterPic2.jpg)

Perfboard with motor wires soldered on (motor wires were initially meant to be connected using header pins on top of the board, but it was found that the end connectors of dupont wires had resistance and lowered the voltage going to the motors, thus wires had to be directly soldered on):
![CopterPic9](./Images/CopterPic9.jpg)
