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
	bool containsTouchLocation(cocos2d::CCPoint point);

	void removeTroops(int troops);
	void addTroops(int troops);

	Player* getOwner();
	void setOwner(Player* owner);

	void setSelected(bool selected);
	void toggleSelected();

private:
	enum zOrder{
		zSelectionGlow,
		zTroopsCount
	};

	Player* owner;
	int troopsCount;
	bool isSelected;

	CCSprite *selection;

	CCLabelTTF* troopsLabel;

	void setupTroopsLabel();

	bool containsPoint(cocos2d::CCPoint point);
};
