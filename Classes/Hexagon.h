#pragma once

#include "Constants.h"
#include "Player.h"

class Addon;

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
	size_t getXCoord() const;
	size_t getYCoord() const;

	int getTroopsCount();
	bool containsTouchLocation(cocos2d::CCTouch *touch);
	bool containsTouchLocation(cocos2d::CCPoint point);

	void removeTroops(int troops);
	void addTroops(int troops);

	Player* getOwner();
	
	void changeOwner(Player* player);

	void setSelected(bool selected);
	void toggleSelected();

	void setAddon(Addon* addon);
    bool hasAddon();
    const Addon* getAddon();
    
	// анимация увеличения / уменьшения
	void runScaleAction();
	void runScaleLabelAction(float maxScale);

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
    CCNode* addonIcon;
	Addon* addon;

	void setupTroopsLabel();

	bool containsPoint(cocos2d::CCPoint point);

	void setOwner(Player* owner);
};
