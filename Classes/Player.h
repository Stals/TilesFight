#pragma once

#include <string>

#include "Constants.h"

class Player{
public:
	Player(const std::string &name, const ccColor3B& color, bool ai);

	std::string getName();
	bool isAI();
	ccColor3B getColor();

private:
	std::string name;
	ccColor3B color;
	bool ai;
};

