#include "Metering.h"

Metering::Metering(int sensorID, double decibels, std::time_t meteringTime)
{
    this->sensorID = sensorID;
    this->decibels = decibels;
    this->meteringTime = meteringTime;
}