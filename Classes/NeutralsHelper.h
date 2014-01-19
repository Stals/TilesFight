#pragma once

#include "TroopsGenerator.h"

// TODO ������������� - ���. ��� ���� ����� �������� � ��� ������������ ����� �������
// ���� �������� ���������� 2 ������, �� ������������ ����� ����� 2

class NeutralsHelper{
public:
	// �� ������� �� ������� ��� ���� �����!
	static void addNeutrals(Player* player, GeneratorType type, size_t x, size_t y);
	static void addNeutrals(Player* player, Player* player2, GeneratorType type, size_t x, size_t y);

private:
	NeutralsHelper();

	static void getSymmetricCoords(size_t x, size_t y, size_t &sym_x, size_t &sym_y);
	static Hexagon* getSymmetricHexagon(Hexagon* hex);
};
