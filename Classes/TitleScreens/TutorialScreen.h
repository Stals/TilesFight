#pragma once

#include "EmptyScreen.h"

class Board;

class TutorialScreen : public EmptyScreen{
public:
    TutorialScreen();

private:
    Board* board;
    
    void setupBoard();
    void setupStep(int stepNum);

    void setupTutorialMove();
    void setupTutorialGenerator();
    void setupTutorialEnd();
};