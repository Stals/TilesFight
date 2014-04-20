//
//  VsAIScreen.cpp
//  HelloCpp
//
//  Created by Stanislav Korotaev on 3/10/14.
//
//

#include "TutorialScreen.h"
#include "../ButtonFactory.h"
#include "Constants.h"
#include "../Game.h"
#include "../Board.h"
#include "../AIButton.h"
#include "../User.h"
#include "../ai/NoAI.h"
#include "../NeutralsHelper.h"
#include "../NeutralsSpawner.h"

#define FONT_SIZE 24.f
#define PADDING -5.f
#define BUTTON_TEXT "GO!"

#define BUTTON_PRIORITY -261

#define HEX_SIZE 64.f //80?


TutorialScreen::TutorialScreen()
{
    setTouchEnabled(true);
    setupStep(0);
}

void TutorialScreen::setupBoard()
{
    const int width = 10;
    const int height = 5;
    
    board = new Board(width, height);
    
    board->setPositionX( (- (width-1) * HEX_SIZE) / 2);
    board->setPositionY( (- (height-2) * HEX_SIZE) / 2);
    
    addChild(board);
    Game::current().setCurrentBoard(board);
}


void TutorialScreen::setupStep(int stepNum)
{
    setupBoard();
    
    Player* player = new Player("PLAYER", hexGreen);
	Player* computer = new Player("AI", hexRed);
    computer->setAI(new NoAI(computer));
    
    NeutralsHelper::addNeutrals(player, computer, TroopsGenerator::Small, 2, 2);
}

void TutorialScreen::setupTutorialMove()
{
    /*
     YOU are Green - и написать цветом это
     To start - just move your armies to the selected sector.
     */
}

void TutorialScreen::setupTutorialGenerator()
{
    /*
     Well done!
        Red one - is your enemy. Захвати generators (маленькие картинки разных) - они приносят войска чтобы победить
     
     !!! ПОСМОТРЕТЬ ЧТО В ГАЛКОНЕ ТОЖЕ
     */
}

void TutorialScreen::setupTutorialEnd()
{
    //кнопку пойти играть против самое слабого бота
    // и текст мол ты ready
    
    // You are ready - now go a and win vs read oponent
}
