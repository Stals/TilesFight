#pragma once

#include "Constants.h"
#include "Board.h"

class GameLayer : public cocos2d::CCLayer
{
public:
	~GameLayer();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	//void update(float dt);	

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

private:
	// implement the "static node()" method manually
    CREATE_FUNC(GameLayer);

	Board* board;
	Player* player;
	Player* computer;
	Player* neutral;

	void setupBoard();
	void setupWalls();
	void setupPlayers();
	void setupNeutrals();

	void createStartingArmy(Player* player, int x, int y);
};
