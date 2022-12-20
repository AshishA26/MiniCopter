# MPU6050 test
## Pins:
- `MPU` --> `Arduino Nano`
- `VCC` --> `Vin`
- `GND` --> `GND`
- `SCL` --> `A5`
- `SDA` --> `A4`
- `INT` --> `D2`

## Instructions:
- In the `MPUTeapot.pde`, you will have to change line 74 to have your COM port (`String portName = "COM12";`) 
- In the `MPU6050_DMP6.ino`, you will have to uncomment `#define OUTPUT_TEAPOT` if you want it to work with the teapot demo, or `#define OUTPUT_READABLE_YAWPITCHROLL` if you want to read the output
