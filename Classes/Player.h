#pragma once

#include <string>
#include <set>

#include "Constants.h"

class AbstractAI;
class Hexagon;

class Player : CCObject{
public:
	Player(const std::string &name, const ccColor3B& color);
	static Player* createNeutral();	
	~Player();

	bool isAI();
	void setAI(AbstractAI* ai);

	std::string getName();
	ccColor3B getColor();
	bool isNeutral();

    // return true if player lost
	bool removeControlledHexagon(Hexagon* hex);
	void addControlledHexagon(Hexagon* hex);

	std::set<Hexagon*>& getControlledHexagons();
    std::vector<Hexagon*> getHexagonsWithTroops();
    std::vector<Hexagon*> getHaxagonsWithGenerators();
    std::vector<Hexagon*> getSelectedHexagons();
    
    void deselectAllHexagons();
    
    int getTroopsPerTick();
    
    //можно ли выделять hexagonы этого игрока
    bool isHexagonsSelectable();

private:
	std::string name;
	ccColor3B color;
	AbstractAI* ai;
	bool neutral;
    
    int troopsPerTick;

	std::set<Hexagon*> controlledHexagons;
    
    bool hasLost();
};

