#include "Game.h"
#include "GameLayer.h"

Game::Game()
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

void Game::starNewGame()
{
    CCScene *pScene = GameLayer::scene();
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
