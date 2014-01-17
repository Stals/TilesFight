#pragma once

#include <string>
#include <set>

#include "Constants.h"

class Hexagon;

class Player{
public:
	Player(const std::string &name, const ccColor3B& color, bool ai);
	static Player* createNeutral();

	std::string getName();
	bool isAI();
	ccColor3B getColor();

	bool isNeutral();

	void removeControlledHexagon(Hexagon* hex);
	void addControlledHexagon(Hexagon* hex);

	std::set<Hexagon*>& getControlledHexagons();

private:
	std::string name;
	ccColor3B color;
	bool ai;
	bool neutral;

	std::set<Hexagon*> controlledHexagons;
};

