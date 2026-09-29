#include <ctime>
#include <string>
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

class Sensor
{
private:
    int id;
    std::string location;
public:
    virtual Metering takeMetering() const = 0;
};

class InSideSensor: public Sensor
{

};
class OutSideSensor: public Sensor
{

};