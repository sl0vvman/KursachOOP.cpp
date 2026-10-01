#include "Sensor.h"
#include <ctime>

void sensorMap::addSensor(Sensor* addingSensor)
{
    citySensors.push_back(addingSensor);
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