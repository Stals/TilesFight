#pragma once

#include "Addon.h"

class AmoutIncreaser : public Addon{
public:
    AmoutIncreaser(Hexagon* hex);
    
    int getAdditionalAmout();
    virtual CCNode* getIcon();

private:
    int additionalAmount;
};