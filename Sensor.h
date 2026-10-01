#pragma once
#include <string>
#include <vector>
#include "Metering.h"

enum class sensorStatus{Active,Inactive};

enum class roomTypeForSensor{livingRoom,officeRoom,industrialRoom};

class Sensor
{
private:
    int id;
    sensorStatus status;
    std::string location;
public:
    virtual Metering takeMetering() const = 0;
    virtual ~Sensor() {}
};


class InSideSensor : public Sensor
{
private:
    roomTypeForSensor roomType;
};
class OutSideSensor : public Sensor
{
private:
    int windSpeed;
    bool isRaining;
};


class SensorFactory
{
public:
    static Sensor* createSensor(const std::string& type, int id, sensorStatus status, const std::string& location);
};

//SensorFactory::createSensor(const std::string& type, int id, sensorStatus sensorStatus, const std::string& location)
//{
//
//}

class sensorMap
{
private:
    std::vector<Sensor*> citySensors;
public:
    sensorMap();
    ~sensorMap();
    void addSensor(Sensor* addingSensor);
    void takeAllSensorMetering();
};
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

