#include "GameLayer.h"
#include "Hexagon.h"
#include "Addons/TroopsGenerator.h"
#include "NeutralsSpawner.h"

#include "utils/RandomGenerator.h"
#include "utils/StringExtension.h"

#include "Game.h"
#include "ai/RandomAI.h"
#include "ai/NoAI.h"

#include "CCShake.h"


USING_NS_CC;


GameLayer::~GameLayer(){
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
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	setTouchEnabled(true);
	
	setupBackgroud();

	setupBoard();
	setupWalls();
	setupPlayers();
	setupNeutrals();
    
    setupListeners();

	return true;
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

void GameLayer::setupPlayers()
{
	player = new Player("Player", hexRed);
	computer = new Player("AI", hexGreen);
	computer->setAI(new RandomAI(computer));

    
    size_t playerY = RandomGenerator::getRandom(1, Game::current().getBoard()->getHeight() - 1);
    size_t enemyY = Game::current().getBoard()->getHeight() - playerY - 1;
    
	createStartingArmy(player, 1, playerY);
	createStartingArmy(computer, 12, enemyY);
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

void GameLayer::setupNeutrals()
{
    NeutralSpawner::current().spawnBigSurroundedGenerator();
    
	for(int i = 0; i < 6; ++i){
        NeutralSpawner::current().spawnRandomCamp();
	}
}

void GameLayer::onPlayerLost(CCObject* obj)
{
    if((Player*)obj == player){
        CCMessageBox("You Loose", "Game Over");
    }else{
        CCMessageBox("You WIN", "Game Over");
    }
    
    Game::current().starNewGame();
    
    //Remove event listener.
    //CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, PLAYER_LOOSE_MGS);
}
