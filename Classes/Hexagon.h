#pragma once

#include "Constants.h"
#include "Player.h"

class TroopsGenerator;

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
	Hexagon(size_t x_coord, size_t y_coord);
	~Hexagon();
	size_t getXCoord();
	size_t getYCoord();

	int getTroopsCount();
	bool containsTouchLocation(cocos2d::CCTouch *touch);
	bool containsTouchLocation(cocos2d::CCPoint point);

	void removeTroops(int troops);
	void addTroops(int troops);

	Player* getOwner();
	
	void changeOwner(Player* player);

	void setSelected(bool selected);
	void toggleSelected();

	void setGenerator(TroopsGenerator* generator);

private:
	enum zOrder{
		zSelectionGlow,
		zGenIcon,
		zTroopsCount
	};

	// положение hexagon'a на board
	size_t x_coord;
	size_t y_coord;

	Player* owner;
	int troopsCount;
	bool isSelected;

	CCSprite *selection;

	CCLabelTTF* troopsLabel;
	TroopsGenerator* generator;

	void setupTroopsLabel();

	bool containsPoint(cocos2d::CCPoint point);

	void setOwner(Player* owner);
};
