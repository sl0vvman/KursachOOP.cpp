#pragma once
#include <string>
#include <vector>
#include "Metering.h"

enum class sensorStatus{Active,Inactive};
enum class sensorType { inside,outside };
enum class roomTypeForSensor{livingRoom,officeRoom,industrialRoom};

class Sensor
{
private:
    int id;
    sensorStatus status;
    std::string location;
public:
    virtual Metering takeMetering() const = 0;
    Sensor(int id, sensorStatus status, const std::string& location);
    virtual ~Sensor() {}
};


class InSideSensor : public Sensor
{
private:
    roomTypeForSensor roomType;
public:
    Metering takeMetering() const override;
    InSideSensor(int id, sensorStatus status, const std::string& location, roomTypeForSensor roomType);
};


class OutSideSensor : public Sensor
{
private:
    int windSpeed;
    bool isRaining;
public:
    Metering takeMetering() const override;
    OutSideSensor(int id, sensorStatus status, const std::string& location,int windSpeed,bool isRaining);
};


class SensorFactory
{
public:
    static Sensor* createSensor(const sensorType type, int id, sensorStatus status, const std::string& location);
};


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


