#include "Sensor.h"
#include "Metering.h"
int main()
{
    NoiseAlert na;
    sensorMap sm;
    NoiseNorm nm;
    NoiseLogger nl;

    SensorFactory sf;
    Sensor* s1 = sf.createSensor(sensorType::outside,123,sensorStatus::Active,timeOfDay::day,roomTypeForSensor::livingRoom,100,true);

    s1->attach(&na);
    s1->attach(&nl);
    sm.addSensor(s1);

    sm.notifyAll(nm);
}

