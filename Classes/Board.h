#pragma once

#include "Constants.h"
#include "Hexagon.h"
#include "HexArray.h"


class Board : public CCLayer{
public:
	Board(int width, int height);

private:
	int width, height;
	HexArray2D hexArray2D;

	void initBoard();
};

// TODO
/*
	����� �������� � ������ ������� ���?
	� ����� ��, ����� ��� ���������� ����� ���. �� ������ ��� ����� ����� ����������� =)
	��� �������, ��� �������?

	������� � ����� ��������� ����� ����� N ���� ������� � ������?
	���� ���.
	������ ������ �� ���������� ����� �� ����� � ���������� ��������� ��� ���������?
	����� ��� ����� ������� �����?
	���� ��� ���� ��� ������� ��� ��������? � �� ������

	HexArray
*/