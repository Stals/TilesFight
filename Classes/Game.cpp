#include "Game.h"
#include "GameLayer.h"
#include "cocos2d.h"
#include "PauseLayer.h"
#include "ResultsLayer.h"

Game::Game():_artScale(1), pausedTargets(0), currentScreen(MENU_SCREEN), currentGameType(WRONG_TYPE)
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

void Game::starNewGame(Player* player1, Player* player2)
{
    CCScene *pScene = GameLayer::scene();
    GameLayer* gameLayer = (GameLayer*)pScene->getChildByTag(1337);
    
    addPlayer(player1);
    addPlayer(player2);
    gameLayer->startGame(player1, player2);
    
    if(CCDirector::sharedDirector()->getRunningScene()){
        CCDirector::sharedDirector()->replaceScene(pScene);
    }else{
        CCDirector::sharedDirector()->runWithScene(pScene);
    }
    
    setCurrentScreen(GAME_SCREEN);
    currentGameType = player2->isAI() ? VS_AI : VS_HUMAN;
}

void Game::restartGame()
{
    // ! TOOD ! убрать clearPlayers из onPlayerLost
    
    // TODO clear player
    // gameLayer->startGame ect ect
}

Game::Type Game::getCurrentGameType()
{
    return currentGameType;
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
            break;
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

void Game::pauseGame(bool showLayer)
{
    // TODO show pause layer
    pausedTargets = CCDirector::sharedDirector()->getScheduler()->pauseAllTargetsWithMinPriority(kCCPriorityNonSystemMin);
    pausedTargets->retain();
    
    if(showLayer){
        CCDirector::sharedDirector()->getRunningScene()->addChild(new PauseLayer, 100500);
    }
    
    setCurrentScreen(PAUSE_SCREEN);
}

void Game::resumeGame()
{
    CCDirector::sharedDirector()->getScheduler()->resumeTargets(pausedTargets);
    pausedTargets->release();
    pausedTargets = 0;
    
    setCurrentScreen(GAME_SCREEN);
}

Game::Screen Game::getCurrentScreen()
{
    return currentScreen;
}

void Game::setCurrentScreen(Screen screen)
{
    currentScreen = screen;
}


