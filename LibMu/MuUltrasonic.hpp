#ifndef __MUULTRASONIC_HPP__
#define __MUULTRASONIC_HPP__

#include "DigitalOut.h"
#include "InterruptIn.h"
#include "PinNames.h"
#include "Timeout.h"
#include "Timer.h"
#include "mbed.h"
#include <chrono>

class MuUltrasonic
{
public:
    MuUltrasonic(PinName trigPin, PinName echoPin, const chrono::microseconds updateSpeed, const chrono::microseconds timeOut);
    MuUltrasonic(PinName trigPin, PinName echoPin, const chrono::microseconds updateSpeed, const chrono::microseconds timeOut, void (*onUpdate)(int));
    ~MuUltrasonic();

    const chrono::microseconds getUpdateSpeed();
    const chrono::microseconds getTimeout();
    void setUpdateSpeed(const chrono::microseconds updateSpeed);
    void setTimeout(const chrono::microseconds timeout);
    void setOnUpdate(void (*onUpdate)(int));

    void startUpdate();
    void pauseUpdate();

    const bool isUpdated();
    const int getCurrentDistance();

    void checkDistance();

private:
    void startTimer();
    void updateDistance();
    void startTrig();

private:
    DigitalOut trig;
    InterruptIn echo;

    chrono::microseconds updateSpeed;
    chrono::microseconds timeout;
    void (*onUpdate)(int);

    Timer timer;
    Timeout tOut;
    volatile int done;
    chrono::microseconds startTime;
    chrono::microseconds endTime;

    float distance;
};

#endif
