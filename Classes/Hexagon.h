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

	void setSelected(bool selected);
	void toggleSelected();

private:
	Player* owner;
	int troopsCount;
	bool isSelected;

	CCLabelTTF* troopsLabel;

	void setupTroopsLabel();
};
