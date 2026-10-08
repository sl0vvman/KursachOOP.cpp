#include "Sensor.h"
#include <ctime>


Sensor::Sensor(int id, sensorStatus status,NoiseObserver* SensorObserver,timeOfDay timeOfDay)
{
    this->id = id;
    this->status = status;
    this->time = timeOfDay;
    this->SensorObserver=SensorObserver;
}
void sensorMap::addSensor(Sensor* addingSensor)
{
    citySensors.push_back(addingSensor);
}

InSideSensor::InSideSensor(int id, sensorStatus status,NoiseObserver* SensorObserver,timeOfDay timeOfDay , roomTypeForSensor roomType) : Sensor(id,status,SensorObserver,timeOfDay)
{
    this->roomType = roomType;
}
Metering InSideSensor::takeMetering() const
{
    std::time_t t;
    return Metering(1,1,t);
}
OutSideSensor::OutSideSensor(int id, sensorStatus status,NoiseObserver* SensorObserver,timeOfDay timeOfDay, int windSpeed, bool isRaining) : Sensor(id, status, SensorObserver,timeOfDay)
{
    this->isRaining = isRaining;
    this->windSpeed = windSpeed;
}
Metering OutSideSensor::takeMetering() const
{
    std::time_t t;
    return Metering(1,1,t);
}
sensorMap::sensorMap()
{

}

sensorMap::~sensorMap()
{
    for (Sensor* sensorPtr : citySensors)
    {
        delete sensorPtr;
    }
    citySensors.clear();
}

Sensor* SensorFactory::createSensor(const sensorType type, int id, sensorStatus status,NoiseObserver* SensorObserver,timeOfDay timeOfDay)
{
    if (type == sensorType::inside)
    {
        roomTypeForSensor rType = roomTypeForSensor::livingRoom;
        return new InSideSensor(id, status,SensorObserver,timeOfDay, rType);
    }
    else if (type == sensorType::outside)
    {
        int windSpeed = 0;
        bool isRaining = false;
        return new OutSideSensor(id, status, SensorObserver,timeOfDay, windSpeed, isRaining);
    }
    return nullptr;
}

