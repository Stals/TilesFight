#pragma once

#include "Constants.h"
#include "Player.h"
#include "Point.h"
#include "Shakable.h"

class Army;
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

class Hexagon : public ShakableSprite{
public:
	Hexagon(size_t x_coord, size_t y_coord);
	~Hexagon();
	size_t getXCoord() const;
	size_t getYCoord() const;
    Point getCoord() const;

	int getTroopsCount();
	bool containsTouchLocation(cocos2d::CCTouch *touch);
	bool containsTouchLocation(cocos2d::CCPoint point);

	void removeTroops(int troops);
	void addTroops(int troops);

	Player* getOwner();
    const Player* getOwner() const;
	
	void changeOwner(Player* player);

    bool isSelected();
	void setSelected(bool selected);
	void toggleSelected();
    bool isSelectable();

	void setAddon(Addon* addon);
    bool hasAddon() const;
    const Addon* getAddon() const;
    
	// ‡ÌËÏ‡ˆËˇ Û‚ÂÎË˜ÂÌËˇ / ÛÏÂÌ¸¯ÂÌËˇ
	void runScaleAction();
	void runScaleLabelAction(float maxScale);
    
    // Armies
    Army* createArmy(Hexagon* destination);
    void removeArmy(Army* army);
    void addArmy(Army *army);
    
    // вызывается Board чтобы определить когда произешел double tap по одному hexagon'у
    void tapped();

private:
	enum zOrder{
		zSelectionGlow,
		zGenIcon,
		zTroopsCount
	};

	// ÔÓÎÓÊÂÌËÂ hexagon'a Ì‡ board
	size_t x_coord;
	size_t y_coord;

	Player* owner;
	int troopsCount;
	bool selected;

	CCSprite *selection;

	CCLabelTTF* troopsLabel;
    CCNode* addonIcon;
	Addon* addon;
    
    CCEaseInOut* scaleAction1;
    CCEaseInOut* scaleAction2;
    
    std::list<Army*> armies;
    
    time_t lastTapTime;

	void setupTroopsLabel();
    void updateTroopsLabel();
    
    void setupSelection();

	bool containsPoint(cocos2d::CCPoint point);

	void setOwner(Player* owner);
    
    // переводит все армии находящиеся на этом секторе в стационарные troops
    void allArmiesToTroops();
    void removeAllArmies();

};
