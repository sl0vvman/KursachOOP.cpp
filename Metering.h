#pragma once
#include <ctime>
#include <iosfwd>

class Metering
{
private:
    int sensorID;
    double decibels;
    std::time_t meteringTime;
public:
    Metering(int sensorID, double decibels, std::time_t meteringTime);
    ~Metering();

    bool isNormslNoise(double limit) const;
    void printTo(std::ostream& out) const;
    void saveTo(std::ostream& out) const;

};
