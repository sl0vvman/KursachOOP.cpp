#pragma once
#include "Metering.h"

class NoiseObserver
{
private:

public:
    virtual void MaxNoiseDetected(const Metering& met) const =0;
    virtual ~NoiseObserver();
};

class NoiseAlert: public NoiseObserver
{
private:

public:
    void MaxNoiseDetected(const Metering& met)const override;
};

class NoiseLogger: public NoiseObserver
{
private:

public:
    void MaxNoiseDetected(const Metering& met)const override;
};

