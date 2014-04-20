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

#define FONT_SIZE 16.f
#define PADDING -5.f
#define BUTTON_TEXT "GO!"

#define BUTTON_PRIORITY -261

#define HEX_SIZE 64.f //80?


TutorialScreen::TutorialScreen()
{
    setTouchEnabled(true);
    setupLabels();
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

void TutorialScreen::setupLabels()
{
    const char* test = "hello world";
    
    CCSize labelSize = CCSizeMake(3.f * HEX_SIZE, 3 * HEX_SIZE);
    
    labelLeft = CCLabelTTF::create(test, default_font.c_str(), FONT_SIZE, labelSize, kCCTextAlignmentCenter);
    labelRight = CCLabelTTF::create(test, default_font.c_str(), FONT_SIZE, labelSize, kCCTextAlignmentCenter);
    
    labelLeft->setPositionX(-getWidth()/2 + labelLeft->getContentSize().width/2);
    labelLeft->setPositionY(-getHeight()/2 + labelLeft->getContentSize().height/2);
    
    labelRight->setPositionX(getWidth()/2 - labelRight->getContentSize().width/2);
    labelRight->setPositionY(-getHeight()/2 + labelRight->getContentSize().height/2);
    
    addChild(labelLeft);
    addChild(labelRight);
}


void TutorialScreen::setupStep(int stepNum)
{
    setupBoard();
    
    if(stepNum == 0){
        setupTutorialMove();
    }
}

// 1)  сделать 2 лейбла который можно менять // причем с автопереносом там вроде было
// 2) сделать первый этап тупо руками
// 3) для второго этапа сделать функцию позволяющую задать кастомное число арсии
        // его же начать использовать внутри
// 4) сделать второй этап
    // где у каждого генератор - но без захвата еще одного ничего не получится
// 5) сделать третий этап
// 6) сделать транизоны
// 7) сделать проверку того что человек сделал что нужно было
    //1
    //2


// 99) добавить картинки во второй этап на право

void TutorialScreen::setupTutorialMove()
{
    labelLeft->setString("you control the green sector. to start just move your armies to the highlighted sector");
    labelRight->setString("to move\ntap on the green sector and without releasing\nmove it onto the highlited sector");
    
    Player* player = new Player("PLAYER", hexGreen);
    Player* computer = new Player("AI", hexRed);
    computer->setAI(new NoAI(computer));
    
    Hexagon* hex = board->at(2, 2);
    hex->changeOwner(player);
    hex->addTroops(10);
    
    Hexagon* selected = board->at(board->getWidth(1) - 2, 2);
    selected->changeOwner(computer);
    selected->setColor(hexDefault);
    selected->setOpacity(127);
    selected->setSelected(true);
    
    /*
     YOU are Green - и написать цветом это
     To start - just move your armies to the selected sector.
     */
    
    // c лева
        // You управляешь green sector. Move it to the highlited sector.
    
    // c справа
        // to move - tap on the green sector and without releasing move it onto the highlited sector.
    
}

void TutorialScreen::setupTutorialGenerator()
{
    /*
     Well done!
        Red one - is your enemy. Захвати generators (маленькие картинки разных) - они приносят войска чтобы победить
     
     !!! ПОСМОТРЕТЬ ЧТО В ГАЛКОНЕ ТОЖЕ
     */
    
    // Штуки с нейтрами не заняты
    // У тебя есть генератор? чтобы ты не мог проиграть вбежав в противника просто
    // у противника точно такойже как у тебя
    
    // С левой стороны слова
        // capture gray generators to have more armies and capture opponents sector.
    // С правой пояснения
        // Generators are sectors with star, or ,or - they generate armies with different speed
    
    
    
     Player* player = new Player("PLAYER", hexGreen);
     Player* computer = new Player("AI", hexRed);
     computer->setAI(new NoAI(computer));
     
     NeutralsHelper::addNeutrals(player, computer, TroopsGenerator::Small, 2, 2);
     
}

void TutorialScreen::setupTutorialEnd()
{
    //кнопку пойти играть против самое слабого бота
    // и текст мол ты ready
    
    // You are ready - now go a and win vs read oponent
    
    // c права
        //Press "GO" to start a game against "Leutnant Gauis"
}
