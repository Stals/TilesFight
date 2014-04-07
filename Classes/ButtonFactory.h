#pragma once

#include "Constants.h"
#include "Button.h"
#include "Handler.h"

enum IconSide{
    ICON_LEFT,
    ICON_RIGHT
};

class ButtonFactory{
public:
    static CCSprite* mainMenuButtonSprite(const char* iconPath, const std::string& text, IconSide side);
    
    static CCSprite* buttonSprite(const std::string& text);
    
    
    static Button* button(const char* iconPath, const std::string& text, IconSide side, Handler* handler, int touchPrority = -255);
    static Button* button(const std::string& text, Handler* handler, int touchPrority = -255);
    
    static Button* imageButton(const char* iconPathInactive, const char* iconPathPressed, Handler* handler, int touchPrority = -255);
};