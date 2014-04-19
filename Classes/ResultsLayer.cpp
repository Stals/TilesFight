//
//  ResultsLayer.cpp
//  HelloCpp
//
//  Created by Stanislav Korotaev on 3/2/14.
//
//

#include "ResultsLayer.h"
#include "Game.h"
#include "achievements/AchievementCounter.h"

ResultsLayer::ResultsLayer(Player* winner, Player* looser)
{
    CounterContainer::current()->setAutoSaveEnabled(true);
    
    button1->setVisible(false);
    
    setupLabel(winner);
    updateAchievements(winner, looser);
}

void ResultsLayer::setupLabel(Player* winner)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    
    CCLabelTTF* label = CCLabelTTF::create(getText(winner).c_str(), default_font.c_str(), 64);
	label->setPosition(ccp(visibleSize.width/2, menu->getPositionY() + button1->getPositionY()));
    
	this->addChild(label);
}

std::string ResultsLayer::getText(Player* winner)
{
    return winner->getName().append(" WINS!");
}

void ResultsLayer::updateAchievements(Player* winner, Player* looser)
{
    CounterContainer::current()->incrementCounter("played_games");
    
    bool playerWon = !winner->isAI();
    
    if(playerWon){
        checkOneTimeAchievements(winner);
    }
    
    if(Game::current().getCurrentGameType() == Game::VS_AI){
        if(playerWon){
            CounterContainer::current()->incrementCounter("victory_vs_ai");
            
            // TODO check for enemies
            // TODO check if all beat give achievement for all ai's
            // скорее всего нужно хранить в игроке если я хочу последенго открывать хитрым способом
            increaseAiCounter(looser);
            
        }else{
            CounterContainer::current()->incrementCounter("loss_vs_ai");
        }
    
    }else{
        CounterContainer::current()->incrementCounter("played_vs_human");
    }
}

void ResultsLayer::checkOneTimeAchievements(Player* winner){
    if(checkTotalControl(winner)){
        CounterContainer::current()->incrementCounter("total_control");
    }
    if(checkNeutralsControl(winner)){
        CounterContainer::current()->incrementCounter("control_neutrals");
    }
}

bool ResultsLayer::checkTotalControl(Player* winner)
{
    Board* board = Game::current().getBoard();
    
    const int height = board->getHeight();
    
    for(int row = 0; row < height; ++row){
        const int width = board->getWidth(row);
        
        for(int col = 0; col < width; ++col){
        
            Hexagon* hex = board->at(col, row);
            if(hex && hex->getOwner() && (hex->getOwner() == winner)){
                ;
            }else{
                return false;
            }
        }
    }
    
    return true;
}

bool ResultsLayer::checkNeutralsControl(Player* winner)
{
    Board* board = Game::current().getBoard();
    
    const int height = board->getHeight();
    
    for(int row = 0; row < height; ++row){
        const int width = board->getWidth(row);
        
        for(int col = 0; col < width; ++col){
            
            Hexagon* hex = board->at(col, row);
            if(hex && hex->hasAddon()){
                
                if(hex->getOwner() != winner){
                    return false;
                }
            }
        }
    }
    
    return true;
}

void ResultsLayer::increaseAiCounter(Player* looser)
{
    if(looser->getName() == "LIEUTENANT"){
    	CounterContainer::current()->incrementCounter("lieutenant");
    }
    else if(looser->getName() == "COMMANDER"){
    	CounterContainer::current()->incrementCounter("commander");
    }
    else if(looser->getName() == "CAPTAIN"){
    	CounterContainer::current()->incrementCounter("captain");
    }
    else if(looser->getName() == "ADMIRAL"){
    	CounterContainer::current()->incrementCounter("admiral");
    }
    else if(looser->getName() == "FLEET ADMIRAL"){
    	CounterContainer::current()->incrementCounter("fleet_admiral");
    }
    
    if(CounterContainer::current()->getCounterAmount("lieutenant") &&
       CounterContainer::current()->getCounterAmount("commander") &&
       CounterContainer::current()->getCounterAmount("captain") &&
       CounterContainer::current()->getCounterAmount("admiral") &&
       CounterContainer::current()->getCounterAmount("fleet_admiral")){
        
        CounterContainer::current()->incrementCounter("beat_all_ai");
    }
}

