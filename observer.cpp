#include "observer.h"
#include <iostream>
NoiseObserver::~NoiseObserver()
{

}
void NoiseAlert::MaxNoiseDetected(const Metering& met) const
{
    std::cout << "ALERT! ";
    met.printTo(std::cout);
}

void NoiseLogger::MaxNoiseDetected(const Metering& met) const
{
    std::cout << "pizda! ";
}
