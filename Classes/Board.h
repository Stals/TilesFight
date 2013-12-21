#pragma once

#include "Constants.h"
#include "Hexagon.h"


class Board : public CCLayer{
public:
	Board(int width, int height);

private:
	int width, height;
	std::vector<std::vector< Hexagon* > > hexagons;

	void initBoard();
};

