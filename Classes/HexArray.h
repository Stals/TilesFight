#pragma once
#include <vector>

#include "Hexagon.h"


// Note: at ������� ����� ���������� NULL ���� �� ���� �������� ������ ���
class HexArray{
public:
	Hexagon* at(size_t index);
	void push_back(Hexagon* hex);

	size_t size();

private:
	std::vector<Hexagon*> row;
};


//2d array of hexes with flat parts on left and right
/*
	 /\
	|  |
	 \/
*/

// NOTE:
/*
	��� �������� ��� ���������� ��� ���
		*****
		 *****
		*****
	��������� ���� ������ ����� ����� �������� ������ �����, ������� ����� ����� �������� �� ��� ������ ������
	������� � ������ ��� ������
	����� ����� ��� ������

	!���� ��!
	����� ����� �������
		 *****
		*****
		 *****
	�� ����� ����� ������ ��������� ����� ����� ��� ����� �����.
	� ����� �� �������� ��� ���� ����� �������� hex ������� ��������� ������ ������. � ���� ��� ��� ��� �����
*/
class HexArray2D
{
public:
	~HexArray2D();

	void addRow();
	HexArray* row(size_t index);
	Hexagon* at(size_t x, size_t y);
	// ���������� hexagon � ������� �� ���������� ���������
	// Note: ����� �������������� �� Hex �� ���� ������ [for(HexSide side = 0; side < HexSidesCount; ++side)]
	Hexagon* sideHexAt(HexSide side, size_t x, size_t y);
	
	size_t size();

	// return true if second is at the side of first
	bool areConnected(Hexagon* first, Hexagon* second);

private:
	std::vector<HexArray* > hexagons;
};

// TODO �������� ��������� Hexagon'a �� ������� � ��� Hexagon?
// ����� �� ��� � array ����?
