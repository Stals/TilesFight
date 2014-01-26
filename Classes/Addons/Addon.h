#pragma once

#include "../Constants.h"
#include "../Hexagon.h"

enum AddonType{
    GeneratorAddon,
    AIncreaserAddon,
    NoAddon
};

class Addon : public CCNode{
public:
    Addon(Hexagon* hex, AddonType type);
    
    virtual CCNode* getIcon() = 0;
    
    AddonType getType() const;
    
protected:
    Hexagon* hex;
    AddonType addonType;
};
