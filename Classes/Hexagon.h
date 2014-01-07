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

class Hexagon : public CCSprite{
public:
	Hexagon();
	int getTroopsCount();
	bool containsTouchLocation(cocos2d::CCTouch *touch);

	void addTroops(int troops);

private:
	int troopsCount;
	CCLabelTTF* troopsLabel;

	void setupTroopsLabel();
};
