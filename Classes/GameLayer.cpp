#include "GameLayer.h"

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

	getHex()->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	getHex()->setPosition(ccp(visibleSize.width/2 + 64, visibleSize.height/2));
	getHex()->setPosition(ccp(visibleSize.width/2 - 64, visibleSize.height/2));

	getHex()->setPosition(ccp(visibleSize.width/2 - 32, visibleSize.height/2 + 48));
	getHex()->setPosition(ccp(visibleSize.width/2 + 32, visibleSize.height/2 + 48));
	getHex()->setPosition(ccp(visibleSize.width/2 - 32, visibleSize.height/2 - 48));
	getHex()->setPosition(ccp(visibleSize.width/2 + 32, visibleSize.height/2 - 48));

	return true;
}

/*
void GameLayer::update(float delta )
{
}*/

CCSprite* GameLayer::getHex()
{
	CCSprite* hex = CCSprite::create("image/hex.png");
	hex->setColor(ccc3(25, 25, 127));
	hex->setScale(0.25f);
	this->addChild(hex);
	return hex;
}