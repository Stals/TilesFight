#include "Game.h"
#include "GameLayer.h"
#include "cocos2d.h"

Game::Game():_artScale(1)
{
}

Game& Game::current()
{
	static Game game;
	return game;
}

void Game::setCurrentBoard(Board* board)
{
	currentBoard = board;
}

Board* Game::getBoard()
{
	return currentBoard;
}

void Game::starNewGame(Game::Type type)
{
    CCScene *pScene = GameLayer::scene();
    GameLayer* gameLayer = (GameLayer*)pScene->getChildByTag(1337);
    gameLayer->setGameType(type);
    
    if(CCDirector::sharedDirector()->getRunningScene()){
        CCDirector::sharedDirector()->replaceScene(pScene);
    }else{
        CCDirector::sharedDirector()->runWithScene(pScene);
    }
}

void Game::addPlayer(Player* player)
{
    players.push_back(player);
}

std::vector<Player*> Game::getPlayers()
{
    return players;
}

void Game::clearPlayers()
{
    while(!players.empty()){
        delete players.back();
        players.pop_back();
    }
}

void Game::checkEndGame()
{
    for(size_t playerID = 0; playerID < players.size(); ++playerID){
        Player* player = players[playerID];
        
        if((!player->isNeutral()) && player->hasLost()){
            cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(PLAYER_LOOSE_MGS.c_str(), player);
        }
    }
}

float Game::artScale()
{
    return _artScale;
}

void Game::setArtScale(float scale)
{
    _artScale = scale;
}
