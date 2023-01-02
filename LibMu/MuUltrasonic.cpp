#include "MuUltrasonic.hpp"
#include "DigitalOut.h"
#include <chrono>
#include <cstdio>

MuUltrasonic::MuUltrasonic(PinName trigPin, PinName echoPin, const chrono::microseconds updateSpeed, const chrono::microseconds timeout)
: trig(trigPin), echo(echoPin)
{
    this->updateSpeed = updateSpeed;
    this->timeout = timeout;
    onUpdate = NULL;
}
MuUltrasonic::MuUltrasonic(PinName trigPin, PinName echoPin, const chrono::microseconds updateSpeed, const chrono::microseconds timeout, void (*onUpdate)(int))
: trig(trigPin), echo(echoPin)
{
    this->updateSpeed = updateSpeed;
    this->timeout = timeout;
    if (onUpdate != NULL)
    {
        this->onUpdate = onUpdate;
        timer.start();
    }
}
MuUltrasonic::~MuUltrasonic() {}

const chrono::microseconds MuUltrasonic::getUpdateSpeed() { return updateSpeed; }
const chrono::microseconds MuUltrasonic::getTimeout() { return timeout; }
void MuUltrasonic::setUpdateSpeed(const chrono::microseconds updateSpeed) { this->updateSpeed = updateSpeed; }
void MuUltrasonic::setTimeout(const chrono::microseconds timeout) { this->timeout = timeout; }
void MuUltrasonic::setOnUpdate(void (*onUpdate)(int)) { if (this->onUpdate != onUpdate) { this->onUpdate = onUpdate; } }

void MuUltrasonic::startTimer()
{
    if (timer.elapsed_time().count() > 600)
    {
        timer.reset();
    }
    startTime = timer.elapsed_time();
}
void MuUltrasonic::updateDistance()
{
    endTime = timer.elapsed_time();
    done = 1;
    distance = (endTime - startTime).count() / 6.0f;
    tOut.detach();
    tOut.attach(callback(this, &MuUltrasonic::startTrig), updateSpeed);
}
void MuUltrasonic::startTrig()
{
    tOut.detach();
    trig.write(1);
    wait_us(10);
    done = 0;
    echo.rise(callback(this, &MuUltrasonic::startTimer));
    echo.fall(callback(this, &MuUltrasonic::updateDistance));
    echo.enable_irq();
    tOut.attach(callback(this, &MuUltrasonic::startTrig), timeout);
    trig.write(0);
}

void MuUltrasonic::startUpdate()
{
    startTrig();
}
void MuUltrasonic::pauseUpdate()
{
    tOut.detach();
    echo.rise(NULL);
    echo.fall(NULL);
}

const bool MuUltrasonic::isUpdated()
{
    return done == 1;
}
const int MuUltrasonic::getCurrentDistance()
{
    return distance;
}

void MuUltrasonic::checkDistance()
{
    if (isUpdated())
    {
        onUpdate(distance);
    }
}