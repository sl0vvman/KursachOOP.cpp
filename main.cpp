#include <ctime>
#include <string>
#include <vector>
class Metering
{
private:
    int sensorID;
    double decibels;
    std::time_t meteringTime;
public:
    Metering(int sensorID,double decibels,std::time_t meteringTime);
    ~Metering();
};

Metering::Metering(int sensorID,double decibels,std::time_t meteringTime)
{
    this->sensorID=sensorID;
    this->decibels=decibels;
    this->meteringTime = meteringTime;
}

enum class sensorStatus
{
    Active,
    Inactive
};

class Sensor
{
private:
    int id;
    sensorStatus sensorStatus;
    std::string location;
public:
    virtual Metering takeMetering() const = 0;
     virtual ~Sensor() {}
};

enum class roomTypeForSensor
{
    livingRoom,
    officeRoom,
    industrialRoom
};
class InSideSensor: public Sensor
{
private:
    roomTypeForSensor roomType;
};
class OutSideSensor: public Sensor
{
private:
    int windSpeed;
    bool isRaining;
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

void sensorMap::addSensor(Sensor* addingSensor)
{
    citySensors.push_back(addingSensor);
}