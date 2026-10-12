#pragma once
#include <map>
#include "Metering.h"
enum class  timeOfDay {day,night};
enum class  placeType {livingRoom, officeRoom, industrialRoom, street};

struct Limits
{
    placeType place;
    timeOfDay time;
    bool operator<(const Limits& other) const
    {
        return std::tie(place, time) < std::tie(other.place, other.time);
    }
};

class NoiseNorm
{
private:
    std::map<Limits,double> limits;
public:
    NoiseNorm();
    void setLimit(placeType place, timeOfDay time, double db);
    bool isExceeded(const Metering& m, placeType place, timeOfDay time) const;
};
