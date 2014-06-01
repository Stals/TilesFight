#pragma once

#include "../Constants.h"
#include "../Hexagon.h"



class Addon : public CCNode{
public:
    enum Type{
        Generator,
        AIncreaser,
        NoAddon
    };
    
    Addon(Hexagon* hex, Addon::Type type);
    
    virtual CCSprite* getIcon() = 0;
    
    Addon::Type getType() const;
    
protected:
    Hexagon* hex;
    Addon::Type addonType;
};
