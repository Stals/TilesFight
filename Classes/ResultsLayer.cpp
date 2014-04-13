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

ResultsLayer::ResultsLayer(Player* winner)
{
    button1->setVisible(false);
    
    setupLabel(winner);
    updateAchievements(winner);
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

void ResultsLayer::updateAchievements(Player* winner)
{
    CounterContainer::current()->incrementCounter("played_games");
    
    bool playerWon = !winner->isAI();
    
    if(Game::current().getCurrentGameType() == Game::VS_AI){
        if(playerWon){
            CounterContainer::current()->incrementCounter("victory_vs_ai");
            
            // TODO check for enemies
            // TODO check if all beat give achievement for all ai's
            // скорее всего нужно хранить в игроке если я хочу последенго открывать хитрым способом
            
        }else{
            CounterContainer::current()->incrementCounter("loss_vs_ai");
        }
    
    }else{
        CounterContainer::current()->incrementCounter("played_vs_human");
    }
}
