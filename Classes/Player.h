#pragma once

#include <string>
#include <set>

#include "Constants.h"

class AbstractAI;
class Hexagon;

class Player{ 
public:
	Player(const std::string &name, const ccColor3B& color);
	static Player* createNeutral();	
	~Player();

	bool isAI();
	void setAI(AbstractAI* ai);

	std::string getName();
	ccColor3B getColor();
	bool isNeutral();

	void removeControlledHexagon(Hexagon* hex);
	void addControlledHexagon(Hexagon* hex);

	std::set<Hexagon*>& getControlledHexagons();

private:
	std::string name;
	ccColor3B color;
	AbstractAI* ai;
	bool neutral;

	std::set<Hexagon*> controlledHexagons;
};

