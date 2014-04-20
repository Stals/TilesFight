#pragma once

#include "EmptyScreen.h"

class Board;

class TutorialScreen : public EmptyScreen{
public:
    TutorialScreen();

private:
    Board* board;
    
    cocos2d::CCLabelTTF* labelLeft;
    cocos2d::CCLabelTTF* labelRight;
    
    void setupLabels();
    
    void setupBoard();
    void setupStep(int stepNum);

    void setupTutorialMove();
    void setupTutorialGenerator();
    void setupTutorialEnd();
    
    void startGame(cocos2d::CCObject* pSender);
};