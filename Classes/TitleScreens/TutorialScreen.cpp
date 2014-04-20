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
#include "../ai/RandomAI.h"

#define FONT_SIZE 16.f
#define PADDING -5.f
#define BUTTON_TEXT "GO!"

#define BUTTON_PRIORITY -261

#define HEX_SIZE 64.f //80?


TutorialScreen::TutorialScreen()
{
    setTouchEnabled(true);
    setupLabels();
    
    // for fast presintation
    static int step = -1;
    if(step < 2){
        ++step;
    }
    setupStep(step);
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
    switch (stepNum) {
        case 0:
            setupBoard();
            setupTutorialMove();
            break;
            
        case 1:
            setupBoard();
            setupTutorialGenerator();
            break;
            
        case 2:
            setupTutorialEnd();
            break;
            
        default:
            setupBoard();
            setupTutorialMove();
    }
}
// 1) сделать проверку того что человек сделал что нужно было
//1
//2
// 2) сделать транизоны


// 99) добавить картинки во второй этап на право


// TOOD запихнуть куда-то
// Note: You can select multiple sectors at a time if you move over it or double tap any your hexagon
void TutorialScreen::setupTutorialMove()
{
    labelLeft->setString("you control the GREEN sector.\nto start\njust move your armies to the highlighted one");
    labelRight->setString("TO MOVE\ntap on the green sector and without releasing\nmove it to the destination");
    
    Player* player = new Player("PLAYER", hexGreen);
    Player* computer = new Player("AI", hexRed);
    computer->setAI(new NoAI(computer));
    
    Hexagon* hex = board->at(3, 2);
    hex->changeOwner(player);
    hex->addTroops(10);
    
    Hexagon* selected = board->at(board->getWidth(1) - 3, 2);
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
    // !!! ПОСМОТРЕТЬ ЧТО В ГАЛКОНЕ ТОЖЕ
    labelLeft->setString("WELL DONE!\nnow you will need to capture gray generators to have more armies and capture opponents sector.");
    labelRight->setString("GENERATORS are sectors with a star, or  ,or   they generate armies with different speed");
    
    Player* player = new Player("PLAYER", hexGreen);
    Player* computer = new Player("AI", hexRed);
    computer->setAI(new NoAI(computer));
    NeutralsHelper::addNeutrals(player, computer, TroopsGenerator::Small, 2, 2);
    
    Player* neutral = Player::createNeutral();
    NeutralsHelper::addNeutrals(neutral, neutral, TroopsGenerator::Large, 0, 4, 1);
    
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
}

void TutorialScreen::setupTutorialEnd()
{
    labelLeft->setString("NICE!\nyou are ready to challange the REAL opponent.");
    labelRight->setString("press \"GO\" to start a game against \"LIEUTENANT GAIUS\"");
    
    Button* button = ButtonFactory::button(BUTTON_TEXT, new Handler(this, callfuncD_selector(TutorialScreen::startGame)), -261);
    
    this->addChild(button);
    
    //кнопку пойти играть против самое слабого бота
    // и текст мол ты ready
    
    // You are ready - now go a and win vs read oponent
    
    // c права
        //Press "GO" to start a game against "Leutnant Gauis"
}

void TutorialScreen::startGame(CCObject* pSender)
{
    Player* player = new Player("PLAYER", hexGreen);
	Player* computer = new Player("LIEUTENANT", hexRed);
    computer->setAI(new RandomAI(computer));
    
    Game::current().starNewGame(player, computer);
}
