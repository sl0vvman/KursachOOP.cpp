#pragma once
#include <string>
class NoiseObserver
{
private:

public:
    virtual void MaxNoiseDetected(int id,std::string location,double decibels) const =0;
    virtual ~NoiseObserver();
};

class NoiseAlert: public NoiseObserver
{
private:

public:
    void MaxNoiseDetected(int id,std::string location,double decibels)const override;
};