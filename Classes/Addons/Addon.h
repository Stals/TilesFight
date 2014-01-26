#pragma once

#include "Hexagon.h"

enum AddonType{
    GeneratorAddon,
    AIncreaserAddon
};

class Addon : public CCNode{
public:
    Addon(Hexagon* hex, AddonType type);
    
    virtual CCNode* getIcon() = 0;
    
    AddonType getType();
    
protected:
    Hexagon* hex;
    AddonType addonType;
};
