#include "AmoutIncreaser.h"
#include "../../lib/utils/StringExtension.h"

AmoutIncreaser::AmoutIncreaser(Hexagon* hex,  AmoutIncreaser::Type type):Addon(hex, Addon::AIncreaser)
{
    switch(type){
        case Small:
            additionalAmount = 1;
            break;
        case Medium:
            additionalAmount = 2;
            break;
        case Large:
            additionalAmount = 3;
            break;
    }
}

int AmoutIncreaser::getAdditionalAmout()
{
    return additionalAmount;
}

CCSprite* AmoutIncreaser::getIcon()
{
    return CCLabelTTF::create(std::string("+").append(StringExtension::toString(additionalAmount)).c_str(), "Arial", 55);
}