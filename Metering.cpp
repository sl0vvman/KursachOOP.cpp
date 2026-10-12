#include "Metering.h"
#include <iosfwd>
#include <ostream>

Metering::Metering(int sensorID, double decibels, std::time_t meteringTime)
{
    this->sensorID = sensorID;
    this->decibels = decibels;
    this->meteringTime = meteringTime;
}
Metering::~Metering()
{

}

bool Metering::isNotNormslNoise(double limit) const
{
    return decibels > limit;
}

void Metering::printTo(std::ostream& out) const
{
    out << "Sensor " << sensorID << ": " << decibels << " dB\n";
}