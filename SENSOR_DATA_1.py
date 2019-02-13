"""
Author:       Patrick Tafoya
Purpose:      Test sensors for pod control systems
              The loop reads and prints all pertinent
              data every half-second
              
              Sensors connected via RPi I2C Bus
              RPi pin 1     3.3V
              RPi pin 3     SDA
              RPi pin 5     SCL
              RPi pin 9     GND
              
              IR THERM
              A5 is SCL
              A4 is SDA
              
              BNO055 ADDRESS 2 requires additional 3.3V to ADR
"""
import smbus
import time
from mlx90614 import MLX90614
from Adafruit_BNO055 import BNO055
from Adafruit_BME280 import BME280

#I2C ADDRESSES FOR SENSORS
IR_ADDRESS = 0x5B
BNO_ADDRESS_A = 0x28
BNO_ADDRESS_B = 0x29
BME280_ADDRESS_A = 0x77
BME280_ADDRESS_B = 0x76
PASC2PSI = 6894.757  #TO CONVERT PASCALS TO PSI

#INITIALIZE SENSORS
IR_Therm = MLX90614(IR_ADDRESS)
IMU_Nose = BNO055.BNO055(None, BNO_ADDRESS_A)
IMU_Tail = BNO055.BNO055(None, BNO_ADDRESS_B)
#
PV1 = BME280(address=BME280_ADDRESS_A)
PV2 = BME280(address=BME280_ADDRESS_B)
#For some brilliant reason the BME280 python library requires that
#temp be read before pressure can be read as the read_raw_temp function
#initializes an attribut required for all other readings"""
t1 = PV1.read_temperature()
t2 = PV2.read_temperature()
#BNO055 LIBRARY REQUIRES self.begin
IMU_Nose.begin()
IMU_Tail.begin()

if __name__ == '__main__':

    while True:
       pressure_1 = PV1.read_pressure() / PASC2PSI
       pressure_2 = PV2.read_pressure() / PASC2PSI
       Temp = IR_Therm.get_obj_temp_F()
       Nose = IMU_Nose.read_euler()
       Tail = IMU_Tail.read_euler()
       Accel_1 = IMU_Nose.read_linear_acceleration()
       Accel_2 = IMU_Tail.read_linear_acceleration()
       print("TEMP:\t%.2f F" % Temp)
       print("PV1:\t%.2f psi" % pressure_1)
       print("PV2:\t%.2f psi" % pressure_2)
       print("NOSE:\tACCELERATION:\t%.2f m/s^2" % Accel_1[0])
       print("X: %.2f\t" % Nose[0], "Y: %.2f\t" % Nose[1], "Z: %.2f" % Nose[2])
       print("TAIL\tACCELERATION:\t%.2f m/s^2" % Accel_2[0])
       print("X: %.2f\t" % Tail[0], "Y: %.2f\t" % Tail[1], "Z: %.2f\n\n" % Tail[2])
       time.sleep(0.5)
