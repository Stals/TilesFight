#pragma once

#include "Addon.h"




class AmoutIncreaser : public Addon{
public:
    enum Type{
        Small,
        Medium,
        Large
    };
    
    AmoutIncreaser(Hexagon* hex, AmoutIncreaser::Type type);
    
    int getAdditionalAmout();
    virtual CCNode* getIcon();

private:
    int additionalAmount;
};