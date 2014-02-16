#pragma once

#include "Constants.h"

enum IconSide{
    ICON_LEFT,
    ICON_RIGHT
};

class ButtonFactory{
public:
    static CCSprite* mainMenuButton(const char* iconPath, const std::string& text, IconSide side);

};