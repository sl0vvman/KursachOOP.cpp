#pragma once
#include <string>
#include <vector>
#include "Metering.h"
#include "observer.h"
#include "NoiseNorms.h"

enum class sensorStatus{Active,Inactive};
enum class sensorType { inside,outside };
enum class roomTypeForSensor{livingRoom,officeRoom,industrialRoom};

class Sensor
{
private:
    int id;
    sensorStatus status;
    timeOfDay time;
    std::vector<NoiseObserver*> observers;
protected:
    virtual placeType place() const = 0;
    Metering makeMetering(double db) const;
public:
    virtual Metering takeMetering() const = 0;
    Sensor(int id, sensorStatus status,timeOfDay timeOfDay);
    void attach(NoiseObserver* observ);
    void Notify(const NoiseNorm& norm) const;
    bool isActive() const;
    virtual ~Sensor();
};


class InSideSensor : public Sensor
{
private:
    roomTypeForSensor roomType;
protected:
    placeType place() const override;
public:
    Metering takeMetering() const override;
    InSideSensor(int id, sensorStatus status,timeOfDay timeOfDay, roomTypeForSensor roomType);
};


class OutSideSensor : public Sensor
{
private:
    int windSpeed;
    bool isRaining;
protected:
    placeType place() const override;
public:
    Metering takeMetering() const override;
    OutSideSensor(int id, sensorStatus status,timeOfDay timeOfDay,int windSpeed,bool isRaining);
};


class SensorFactory
{
public:
    static Sensor* createSensor(sensorType type, int id, sensorStatus status, timeOfDay part, roomTypeForSensor room = roomTypeForSensor::livingRoom,int windSpeed = 0, bool isRaining = false);
};


class sensorMap
{
private:
    std::vector<Sensor*> citySensors;
public:
    sensorMap();
    sensorMap(const sensorMap&) = delete;
    sensorMap& operator=(const sensorMap&) = delete;
    ~sensorMap();
    void addSensor(Sensor* addingSensor);  
    void notifyAll(const NoiseNorm& norm) const;
};


