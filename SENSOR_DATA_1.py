import smbus
import time
from mlx90614 import MLX90614
from Adafruit_BNO055 import BNO055
from Adafruit_BME280 import BME280


IR_ADDRESS = 0x5B
BNO_ADDRESS_A = 0x28
BNO_ADDRESS_B = 0x29
BME280_ADDRESS_A = 0x77
BME280_ADDRESS_B = 0x76
PASC2PSI = 6894.757


IR_Therm = MLX90614(IR_ADDRESS)
IMU_Nose = BNO055.BNO055(None, BNO_ADDRESS_A)
IMU_Tail = BNO055.BNO055(None, BNO_ADDRESS_B)
PV1 = BME280(4, 4, 4, 3, 0, BME280_ADDRESS_A)
PV2 = BME280(4, 4, 4, 3, 0, BME280_ADDRESS_B)
#NEED TO READ TEMP ON BME280 TO GET PRESSURE...
t1 = PV1.read_temperature()
t2 = PV2.read_temperature()

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
       #print("ACCELERATION: %.2f m/s^2\t" %Accel_1[0], "%.2f m/s^s\n\n" %Accel_2[0])
       time.sleep(0.5)
