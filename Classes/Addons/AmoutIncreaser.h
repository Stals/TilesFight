#pragma once

#include "Addon.h"

enum AIncreaserType{
	SmallAInc,
	MediumAInc,
	LargeAInc
};


class AmoutIncreaser : public Addon{
public:
    AmoutIncreaser(Hexagon* hex, AIncreaserType type);
    
    int getAdditionalAmout();
    virtual CCNode* getIcon();

private:
    int additionalAmount;
};