#pragma once
#include <ctime>
class Metering
{
private:
    int sensorID;
    double decibels;
    std::time_t meteringTime;
public:
    Metering(int sensorID, double decibels, std::time_t meteringTime);
    ~Metering();
};
