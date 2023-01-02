#include "mbed.h"

#include "LibMu/MuUltrasonic.hpp"

void distanceUpdate(int distance)
{
    printf("Distance: %d\n", distance);
}

// main() runs in its own thread in the OS
int main()
{
    MuUltrasonic ultrasonic(PC_10, PC_12, 100ms, 1s, &distanceUpdate);

    ultrasonic.startUpdate();
    while (true) {
        ultrasonic.checkDistance();
    }
}