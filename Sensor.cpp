#include "Sensor.h"
#include <ctime>


Sensor::Sensor(int id, sensorStatus status,timeOfDay timeOfDay)
{
    this->id = id;
    this->status = status;
    this->time = timeOfDay;
}
Sensor::~Sensor()
{

}
bool Sensor::isActive() const
{
    if(status==sensorStatus::Active)return true;
    else return false;
}
void Sensor::attach(NoiseObserver* observ)
{
    observers.push_back(observ);
}
void Sensor::Notify(double limit) const
{
    if(!isActive())return;
    Metering m = takeMetering();
    if(m.isNormslNoise(limit))
    {
        for(NoiseObserver* observ:observers)
        {
            observ->MaxNoiseDetected(m);
        }
    }
}
Metering Sensor::makeMetering(double db) const
{
    return Metering(id, db, std::time(nullptr));
}
void sensorMap::addSensor(Sensor* addingSensor)
{
    citySensors.push_back(addingSensor);
}

InSideSensor::InSideSensor(int id, sensorStatus status,timeOfDay timeOfDay , roomTypeForSensor roomType) : Sensor(id,status,timeOfDay)
{
    this->roomType = roomType;
}
Metering InSideSensor::takeMetering() const
{
    double db=30;
    if(roomType==roomTypeForSensor::industrialRoom)db+=15;
    else if(roomType==roomTypeForSensor::livingRoom)db+=5;
    else db+=10;
    return makeMetering(db);
}
OutSideSensor::OutSideSensor(int id, sensorStatus status,timeOfDay timeOfDay, int windSpeed, bool isRaining) : Sensor(id, status,timeOfDay)
{
    this->isRaining = isRaining;
    this->windSpeed = windSpeed;
}

Metering OutSideSensor::takeMetering() const
{
    double db = 40 + windSpeed * 0.3;
    if(isRaining)db+=5;
    return makeMetering(db);
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

void sensorMap::takeAllSensorMetering()
{

}

Sensor* SensorFactory::createSensor(const sensorType type, int id, sensorStatus status,timeOfDay timeOfDay)
{
    if (type == sensorType::inside)
    {
        roomTypeForSensor rType = roomTypeForSensor::livingRoom;
        return new InSideSensor(id, status,timeOfDay, rType);
    }
    else if (type == sensorType::outside)
    {
        int windSpeed = 0;
        bool isRaining = false;
        return new OutSideSensor(id, status,timeOfDay, windSpeed, isRaining);
    }
    return nullptr;
}

