#pragma once

#include "TroopsGenerator.h"

// TODO переименовать - так. как этот класс подойдет и для расположения арсий игроков

class NeutralsHelper{
public:
	// TODO должен не спавнить на игроках или мимо краты!
	static void addNeutrals(Player* player, GeneratorType type, size_t x, size_t y);

private:
	NeutralsHelper();

	static void getSymmetricCoords(size_t x, size_t y, size_t &sym_x, size_t &sym_y);
	static Hexagon* getSymmetricHexagon(Hexagon* hex);
};
