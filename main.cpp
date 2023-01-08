#include "PinNameAliases.h"
#include "PinNames.h"
#include "mbed.h"


/* 
* MuUltrasonic use sample
*/
// #include "LibMu/MuUltrasonic.hpp"

// void distanceUpdate(int distance)
// {
//     printf("Distance: %d\n", distance);
// }

// // main() runs in its own thread in the OS
// int main()
// {
//     MuUltrasonic ultrasonic(PC_10, PC_12, 100ms, 1s, &distanceUpdate);

//     ultrasonic.startUpdate();
//     while (true) {
//         ultrasonic.checkDistance();
//     }
// }


/*
* MuMPU9250 use sample
*/
#include "MuMPU9250.hpp"

int main()
{
    MPU9250 mpu9250(D14, D15);
    int16_t accelData[3], gyroData[3], magData[3];

    mpu9250.resetMPU9250();
    mpu9250.MPU9250SelfTest(mpu9250.SelfTest);
    printf("x-axis self test: acceleration trim within: %f pct of factory value\n\r", mpu9250.SelfTest[0]);  
	printf("y-axis self test: acceleration trim within: %f pct of factory value\n\r", mpu9250.SelfTest[1]);  
	printf("z-axis self test: acceleration trim within: %f pct of factory value\n\r", mpu9250.SelfTest[2]);  
	printf("x-axis self test: gyration trim within: %f pct of factory value\n\r", mpu9250.SelfTest[3]);  
	printf("y-axis self test: gyration trim within: %f pct of factory value\n\r", mpu9250.SelfTest[4]);  
	printf("z-axis self test: gyration trim within: %f pct of factory value\n\r", mpu9250.SelfTest[5]);  
    mpu9250.getAres();
    mpu9250.getGres();
    mpu9250.getMres();
    printf("Accelerometer sensitivity is %f LSB/g \n\r", 1.0f/mpu9250.aRes);
	printf("Gyroscope sensitivity is %f LSB/deg/s \n\r", 1.0f/mpu9250.gRes);
	printf("Magnetometer sensitivity is %f LSB/G \n\r", 1.0f/mpu9250.mRes);

    while (1)
    {
        mpu9250.readAccelData(accelData);
        printf("accel: %d, %d, %d\n", *accelData, *(accelData + 1), *(accelData + 2));
        wait_us(100000);

        mpu9250.readGyroData(gyroData);
        printf("gyro: %d, %d, %d\n", *gyroData, *(gyroData + 1), *(gyroData + 2));
        wait_us(100000);

        mpu9250.readMagData(magData);
        printf("mag: %d, %d, %d\n\n\n", *magData, *(magData + 1), *(magData + 2));
        wait_us(100000);
    }
}