#pragma once

#include "Constants.h"
#include "Player.h"

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

	Player* getOwner();
	void setOwner(Player* owner);

private:
	Player* owner;

	int troopsCount;
	CCLabelTTF* troopsLabel;

	void setupTroopsLabel();
};
