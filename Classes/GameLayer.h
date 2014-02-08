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
	enum zOrder{
		zBackground,
		zBoard
	};

	// implement the "static node()" method manually
    CREATE_FUNC(GameLayer);

	Board* board;
	Player* player;
	Player* computer;

	void setupBackgroud();

	void setupBoard();
	void setupWalls();
	void setupPlayers();
	void setupNeutrals();
    // может перенести в Game?
    void setupListeners();

	void createStartingArmy(Player* player, int x, int y);
    void createStartingArmies(Player* player, Player* player2, size_t playerX, size_t playerY);

    
    void onPlayerLost(CCObject* obj);
    
    void checkEndGame(float dt);
};
