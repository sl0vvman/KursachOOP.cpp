#include"NoiseNorms.h"

NoiseNorm::NoiseNorm() //рб санпин 115
{
    setLimit(placeType::livingRoom,timeOfDay::day,40);
    setLimit(placeType::livingRoom,timeOfDay::night,30);
    setLimit(placeType::officeRoom,timeOfDay::day,50);
    setLimit(placeType::officeRoom,timeOfDay::night,50);
    setLimit(placeType::industrialRoom,timeOfDay::day,80);
    setLimit(placeType::industrialRoom,timeOfDay::night,80);
    setLimit(placeType::street,timeOfDay::day,55);
    setLimit(placeType::street,timeOfDay::night,45);
}

void NoiseNorm::setLimit(placeType place, timeOfDay time, double db)
{
    limits[{place, time}] = db;
}

bool NoiseNorm::isExceeded(const Metering& m, placeType place, timeOfDay time) const
{
    auto it = limits.find({ place, time });
    if (it != limits.end())
    {
        return m.isNotNormslNoise(it->second);
    }
    return false;
}