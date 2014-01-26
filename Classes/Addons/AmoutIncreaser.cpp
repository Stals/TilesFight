#include "AmoutIncreaser.h"
#include "../utils/StringExtension.h"


AmoutIncreaser::AmoutIncreaser(Hexagon* hex):Addon(hex)
{
    additionalAmount = 3;
}

int AmoutIncreaser::getAdditionalAmout()
{
    return additionalAmount;
}

CCNode* AmoutIncreaser::getIcon()
{
    return CCLabelTTF::create(std::string("+").append(StringExtension::toString(additionalAmount)).c_str(), default_font.c_str(), 10);
}