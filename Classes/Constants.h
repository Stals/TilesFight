#pragma once
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

using namespace cocos2d;

const ccColor3B hexBlue(ccc3(25, 25, 127));
const ccColor3B hexRed(ccc3(127, 25, 25));
const ccColor3B hexGreen(ccc3(25, 127, 25));
const ccColor3B hexGray(ccc3(127, 127, 127));

inline float scaledWidth(CCSprite* sprite)
{
	return sprite->getContentSize().width * sprite->getScaleX();
}

inline float scaledHeight(CCSprite* sprite)
{
	return sprite->getContentSize().height * sprite->getScaleY();
}
