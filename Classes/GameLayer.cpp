#include "GameLayer.h"
#include "Hexagon.h"
#include "Addons/TroopsGenerator.h"
#include "NeutralsSpawner.h"
#include "PauseLayer.h"
#include "ResultsLayer.h"

#include "../lib/utils/RandomGenerator.h"
#include "../lib/utils/StringExtension.h"

#include "Game.h"
#include "ai/RandomAI.h"
#include "ai/NoAI.h"
#include "ai/ExpansionAI.h"
#include "ai/ConquerorAI.h"
#include "MusicPlayer.h"

#include "CCShake.h"

#define CHECK_ENDGAME_DELAY 1.f

USING_NS_CC;


GameLayer::~GameLayer(){
    //delete board;
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, PLAYER_LOOSE_MGS.c_str());
}


CCScene* GameLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer, 0, 1337);

    // return the scene
    return scene;
}

#include "NeutralsHelper.h"

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    //CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	setTouchEnabled(true);
	
	setupBackgroud();
    setupPause();

	setupBoard();
	
    setupListeners();
    MusicPlayer::playBattleMusic();
    
    this->schedule(schedule_selector(GameLayer::checkEndGame), CHECK_ENDGAME_DELAY, kCCRepeatForever, CHECK_ENDGAME_DELAY);
	return true;
}


void GameLayer::startGame(Player* player1, Player* player2)
{
    setupPlayers(player1, player2);
    setupWalls();
	setupNeutrals();
}


void GameLayer::setupBackgroud()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	std::string file = IMG((std::string("bg") +
		StringExtension::toString(RandomGenerator::getRandom(1, 12)) + ".jpg"));
	CCLog("%s", file.c_str());

	CCSprite* bg = CCSprite::create(file.c_str());
	bg->setScale(0.8f);
	bg->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	addChild(bg, zBackground);
}

void GameLayer::setupPause()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* buttonImage = CCSprite::create(IMG("pause.png"));
    CCMenuItemSprite* button = CCMenuItemSprite::create(buttonImage, buttonImage, buttonImage,
                                                        this, menu_selector(GameLayer::onPauseButtonPressed));

    CCMenu* menu = CCMenu::create(button, NULL);
    this->addChild(menu, zPause);
    
    const float padding = 3;
    menu->setPosition(ccp(button->getContentSize().width + padding, winSize.height - button->getContentSize().height - padding));
    
}

void GameLayer::setupBoard()
{
	board = new Board(15, 15);
	board->setPosition(ccp(64, 48));
	addChild(board, zBoard);

	Game::current().setCurrentBoard(board);
}

void GameLayer::setupWalls()
{
}

void GameLayer::setupPlayers(Player* player1, Player* player2)
{
    player = player1;
    computer = player2;
    
    const size_t playerX = 1;
    const size_t playerY = RandomGenerator::getRandom(1, Game::current().getBoard()->getHeight() - 1);
    
    createStartingArmies(player1, player2, playerX, playerY);
}

void GameLayer::setupListeners()
{
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameLayer::onPlayerLost), PLAYER_LOOSE_MGS.c_str(), NULL);
}

void GameLayer::createStartingArmy(Player* player, int x, int y)
{
	Hexagon* centerHex = board->at(x, y);
	centerHex->changeOwner(player);
	centerHex->addTroops(25);

	centerHex->setAddon(new TroopsGenerator(centerHex, TroopsGenerator::Large));

	for(int side = 0; side < HexSidesCount; ++side)
	{
		Hexagon* hex = board->sideHexAt((HexSide)side, x, y);
		if(hex){
			hex->changeOwner(player);
			hex->addTroops(5);
			hex->setAddon(new TroopsGenerator(hex, TroopsGenerator::Small));
        }
	}
}

void GameLayer::createStartingArmies(Player* player, Player* player2, size_t playerX, size_t playerY)
{
    NeutralsHelper::addNeutrals(player, player2, TroopsGenerator::Large, playerX, playerY);
    
    for(int side = 0; side < HexSidesCount; ++side){
        Hexagon* hex = board->sideHexAt((HexSide)side, playerX, playerY);
		if(hex){
            NeutralsHelper::addNeutrals(player, player2, TroopsGenerator::Small, hex->getXCoord(), hex->getYCoord());
        }
    }
}

void GameLayer::setupNeutrals()
{
    NeutralSpawner::current().spawnBigSurroundedGenerator();
    
	for(int i = 0; i < 5; ++i){
        NeutralSpawner::current().spawnRandomCamp();
	}
}

void GameLayer::onPlayerLost(CCObject* obj)
{
    //Remove event listener.
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, PLAYER_LOOSE_MGS.c_str());
    
    // TODO должно делаться если игра перезапускается или выклчючется без этого
    this->unschedule(schedule_selector(GameLayer::checkEndGame));
    
    board->setTouchEnabled(false);
    Game::current().pauseGame(false);
    
    if((Player*)obj == player){
        addChild(new ResultsLayer(computer), zPause);

    }else{
        addChild(new ResultsLayer(player), zPause);
    }
    
    Game::current().clearPlayers();
}

void GameLayer::onPauseButtonPressed(CCObject* obj)
{
    Game::current().pauseGame();
}

void GameLayer::checkEndGame(float dt)
{
    Game::current().checkEndGame();
}

