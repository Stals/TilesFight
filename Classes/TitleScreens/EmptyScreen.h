#pragma once

#include "cocos2d.h"

class EmptyScreen: public cocos2d::CCLayer{
public:
    EmptyScreen();
    virtual ~EmptyScreen();

    virtual float getHeight();
    virtual float getWidth();
};