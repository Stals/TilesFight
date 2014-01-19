#pragma once

#include "TroopsGenerator.h"

// TODO ������������� - ���. ��� ���� ����� �������� � ��� ������������ ����� �������

class NeutralsHelper{
public:
	// TODO ������ �� �������� �� ������� ��� ���� �����!
	static void addNeutrals(Player* player, GeneratorType type, size_t x, size_t y);

private:
	NeutralsHelper();

	static void getSymmetricCoords(size_t x, size_t y, size_t &sym_x, size_t &sym_y);
	static Hexagon* getSymmetricHexagon(Hexagon* hex);
};
