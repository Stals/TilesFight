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
	Может хранение и доступ вынести еще?
	я думаю да, тогда при добавлении будет изи. но внутри там будет замес происходить =)
	Как назвать, как хранить?

	Создать я думаю создавать сразу через N типо сколько в строке?
	Хотя нет.
	Просто смотря на количество строк он будет с правильным смещением уже добавлять?
	тогда мне нужно зарание знать?
	Либо там было как зранить без смещений? я не уверен

	HexArray
*/