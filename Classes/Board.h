#pragma once

#include "Constants.h"
#include "Hexagon.h"
#include "HexArray.h"


class Board : public CCLayer{
public:
	Board(int width, int height);

	Hexagon* at(size_t x, size_t y);
	Hexagon* sideHexAt(HexSide side, size_t x, size_t y);

	void moveTroops(Hexagon * startHex, Hexagon* endHex);

	int getWidth(size_t row);
	int getHeight();

private:
	int width, height;
	HexArray2D hexArray2D;

	void initBoard();

	void getStartEndHex(CCTouch* touch, Hexagon*& startHex, Hexagon*& endHex);	
	
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
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