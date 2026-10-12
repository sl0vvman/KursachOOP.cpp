#include"NoiseNorms.h"

NoiseNorm::NoiseNorm()
{
    setLimit(placeType::livingRoom,     timeOfDay::day,   40);
    setLimit(placeType::livingRoom,     timeOfDay::night, 30);
    setLimit(placeType::officeRoom,     timeOfDay::day,   50);
    setLimit(placeType::officeRoom,     timeOfDay::night, 50);
    setLimit(placeType::industrialRoom, timeOfDay::day,   80);
    setLimit(placeType::industrialRoom, timeOfDay::night, 80);
    setLimit(placeType::street,         timeOfDay::day,   55);
    setLimit(placeType::street,         timeOfDay::night, 45);
}

void NoiseNorm::setLimit(placeType place, timeOfDay time, double db)
{
    limits[{place, time}] = db;
}

bool NoiseNorm::isExceeded(const Metering& m, placeType place, timeOfDay time) const
{
    if (auto it = limits.find({place, time}); it != limits.end()) {
        return m.isNormslNoise(it->second);
    }
    return false;
}