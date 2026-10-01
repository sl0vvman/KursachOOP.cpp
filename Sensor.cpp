#include "Sensor.h"
#include <ctime>


Sensor::Sensor(int id, sensorStatus status, const std::string& location)
{
    this->id = id;
    this->status = status;
    this->location = location;
}
void sensorMap::addSensor(Sensor* addingSensor)
{
    citySensors.push_back(addingSensor);
}

InSideSensor::InSideSensor(int id, sensorStatus status, const std::string& location, roomTypeForSensor roomType) : Sensor(id,status,location)
{
    this->roomType = roomType;
}
OutSideSensor::OutSideSensor(int id, sensorStatus status, const std::string& location, int windSpeed, bool isRaining) : Sensor(id, status, location)
{
    this->isRaining = isRaining;
    this->windSpeed = windSpeed;
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

Sensor* SensorFactory::createSensor(const sensorType type, int id, sensorStatus status, const std::string& location)
{
    if (type == sensorType::inside)
    {
        roomTypeForSensor rType = roomTypeForSensor::livingRoom;
        return new InSideSensor(id, status, location, rType);
    }
    else if (type == sensorType::outside)
    {
        int windSpeed = 0;
        bool isRaining = false;
        return new OutSideSensor(id, status, location, windSpeed, isRaining);
    }
    return nullptr;
}

