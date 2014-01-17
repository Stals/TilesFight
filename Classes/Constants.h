#pragma once
//#include "SimpleAudioEngine.h"
#include "cocos2d.h"


#ifdef __APPLE__
#define FONT(var) var
#else
#define FONT(var) std::string("fonts/").append(var).append(".ttf")
#endif


using namespace cocos2d;

const ccColor3B hexBlue(ccc3(25, 25, 150));
const ccColor3B hexRed(ccc3(150, 25, 25));
const ccColor3B hexGreen(ccc3(25, 150, 25));
const ccColor3B hexDark(ccc3(45, 45, 45)); // border / wall color
const ccColor3B hexGray(ccc3(127, 127, 127));
const ccColor3B hexWhite(ccc3(245, 245, 245));

const ccColor3B hexDefault(hexGray);
// yellow

// вокруг поставить дефайн который будет добавлять вначало папки и в конец ттф если это иос
const std::string default_font = FONT("GAMECUBEN");

inline float scaledWidth(CCSprite* sprite)
{
	return sprite->getContentSize().width * sprite->getScaleX();
}

inline float scaledHeight(CCSprite* sprite)
{
	return sprite->getContentSize().height * sprite->getScaleY();
}
