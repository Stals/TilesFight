#include "GameLayer.h"
#include "Hexagon.h"
#include "TroopsGenerator.h"


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
	

	setupBoard();
	setupWalls();
	setupPlayers();
	setupNeutrals();

	return true;
}

void GameLayer::setupBoard()
{
	board = new Board(15, 15);
	board->setPosition(ccp(64, 48));
	addChild(board);
}

void GameLayer::setupWalls()
{
}

void GameLayer::setupPlayers()
{
	player = new Player("Player", hexRed, false);
	computer = new Player("AI", hexGreen, true);

	createStartingArmy(player, 1, 7);
	createStartingArmy(computer, 12, 7);
}
void GameLayer::createStartingArmy(Player* player, int x, int y)
{
	const ccColor3B playerColor = player->getColor();
	Hexagon* centerHex = board->at(x, y);
	centerHex->setOwner(player);
	centerHex->addTroops(25);

	centerHex->setGenerator(new TroopsGenerator(centerHex, LargeGen));

	for(int side = 0; side < HexSidesCount; ++side)
	{
		Hexagon* hex = board->sideHexAt((HexSide)side, x, y);
		if(hex){
			hex->setOwner(player);
			hex->addTroops(5);
			hex->setGenerator(new TroopsGenerator(hex, SmallGen));
		}
	}
}

void GameLayer::setupNeutrals()
{
}
