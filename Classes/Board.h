#pragma once

#include "Constants.h"
#include "Hexagon.h"
#include "HexArray.h"


class Board : public CCLayer{
public:
	Board(int width, int height);

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
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