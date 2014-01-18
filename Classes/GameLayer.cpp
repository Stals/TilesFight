#include "GameLayer.h"
#include "Hexagon.h"
#include "TroopsGenerator.h"
#include "utils/RandomGenerator.h"
#include "utils/StringExtension.h"

#include "Game.h"
#include "ai/RandomAI.h"
#include "ai/NoAI.h"

USING_NS_CC;


GameLayer::~GameLayer(){
	while(!neutrals.empty()) {
		delete neutrals.back();
		neutrals.pop_back();
	}
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

	return true;
}

void GameLayer::setupBackgroud()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	std::string file = (std::string("image/bg") +
		StringExtension::toString(RandomGenerator::getRandom(1, 5)) + ".jpg");
	CCLog("%s", file.c_str());

	CCSprite* bg = CCSprite::create(file.c_str());
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

	createStartingArmy(player, 1, 7);
	createStartingArmy(computer, 12, 7);
}
void GameLayer::createStartingArmy(Player* player, int x, int y)
{
	const ccColor3B playerColor = player->getColor();
	Hexagon* centerHex = board->at(x, y);
	centerHex->changeOwner(player);
	centerHex->addTroops(25);

	centerHex->setGenerator(new TroopsGenerator(centerHex, LargeGen));

	for(int side = 0; side < HexSidesCount; ++side)
	{
		Hexagon* hex = board->sideHexAt((HexSide)side, x, y);
		if(hex){
			hex->changeOwner(player);
			hex->addTroops(5);
			hex->setGenerator(new TroopsGenerator(hex, SmallGen));
		}
	}
}

void GameLayer::setupNeutrals()
{
	Player* neutral = Player::createNeutral();
	neutral->setAI(new NoAI(neutral));
	neutrals.push_back(neutral);

	createStartingArmy(neutral, 6, 4);
	createStartingArmy(neutral, 7, 10);
}
