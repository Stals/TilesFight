#pragma once

#include <string>

#include "Constants.h"

class Player{
public:
	Player(const std::string &name, const ccColor3B& color, bool ai);
	static Player* createNeutral();

	std::string getName();
	bool isAI();
	ccColor3B getColor();

	bool isNeutral();
private:
	std::string name;
	ccColor3B color;
	bool ai;

	bool neutral;
};

