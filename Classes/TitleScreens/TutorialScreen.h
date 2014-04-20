#pragma once

#include "EmptyScreen.h"

class Board;
class Player;

class TutorialScreen : public EmptyScreen{
public:
    TutorialScreen();
    virtual ~TutorialScreen();
private:
    Board* board;
    int currentStep;
    
    Player* player;
    Player* computer;
    
    cocos2d::CCLabelTTF* labelLeft;
    cocos2d::CCLabelTTF* labelRight;
    
    void setupLabels();
    
    void setupBoard();
    void setupStep(int stepNum);

    void setupTutorialMove();
    void setupTutorialGenerator();
    void setupTutorialEnd();
    
    void startGame(cocos2d::CCObject* pSender);
    
    void checkStepComplete(float dt);
    void onPlayerLost(CCObject* obj);
};