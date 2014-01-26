#include "AmoutIncreaser.h"
#include "../utils/StringExtension.h"

AmoutIncreaser::AmoutIncreaser(Hexagon* hex,  AIncreaserType type):Addon(hex, AIncreaserAddon)
{
    switch(type){
        case SmallAInc:
            additionalAmount = 1;
            break;
        case MediumAInc:
            additionalAmount = 2;
            break;
        case LargeAInc:
            additionalAmount = 3;
            break;
    }
}

int AmoutIncreaser::getAdditionalAmout()
{
    return additionalAmount;
}

CCNode* AmoutIncreaser::getIcon()
{
    return CCLabelTTF::create(std::string("+").append(StringExtension::toString(additionalAmount)).c_str(), "Arial", 55);
}