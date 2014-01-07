#pragma once

#include "Constants.h"

enum HexSide{
	HexTopLeft,
	HexTopRight,
	HexLeft,
	HexRight,
	HexBottomLeft,
	HexBottomRight,
	HexSidesCount
};

class Hexagon : public CCSprite/*, public cocos2d::CCTargetedTouchDelegate*/{
public:
	Hexagon();

	bool containsTouchLocation(cocos2d::CCTouch *touch);

private:
    cocos2d::CCRect rect();
};
