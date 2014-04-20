#pragma once

#include "cocos2d.h"

class EmptyScreen: public cocos2d::CCLayer{
public:
    EmptyScreen();
    virtual ~EmptyScreen();

    static float getHeight();
    static float getWidth();
};