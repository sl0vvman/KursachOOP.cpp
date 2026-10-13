#include "Sensor.h"
#include <ctime>
#include<random>

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
void Sensor::Notify(const NoiseNorm& norm) const
{
    if(!isActive())return;
    Metering m = takeMetering();
    if(norm.isExceeded(m, place(), time))
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
placeType InSideSensor::place() const
{
    placeType target = placeType::none;
    switch (roomType)
    {
    case roomTypeForSensor::livingRoom:
    {
        target = placeType::livingRoom;
        break;
    }
    case roomTypeForSensor::officeRoom:
    {
        target = placeType::officeRoom;
        break;
    }
    case roomTypeForSensor::industrialRoom:
    {
        target = placeType::industrialRoom;
        break;
    }
    default:
    {
        break;
    }
    }

    return target;
}
Metering InSideSensor::takeMetering() const
{
    std::random_device randDev;
    std::mt19937 gen(randDev());
    std::uniform_int_distribution<int> distrib(25,35);
    double db=distrib(randDev);

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

placeType OutSideSensor::place() const 
{
    return placeType::street;
}

Metering OutSideSensor::takeMetering() const
{
    std::random_device randDev;
    std::mt19937 gen(randDev());
    std::uniform_int_distribution<int> distrib(35,45);
    double db=distrib(randDev) + windSpeed * 0.3;;

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

void sensorMap::notifyAll(const NoiseNorm& norm) const
{
    for (Sensor* sensorPtr : citySensors)
    {
        sensorPtr->Notify(norm);
    }
}

Sensor* SensorFactory::createSensor(sensorType type, int id, sensorStatus status, timeOfDay part,roomTypeForSensor room, int windSpeed, bool isRaining)
{
    if (type == sensorType::inside)
    {
        return new InSideSensor(id, status, part, room);
    }
    if (type == sensorType::outside)
    {
        return new OutSideSensor(id, status, part, windSpeed, isRaining);
    }
    return nullptr;
}

