//
//  ResultsLayer.cpp
//  HelloCpp
//
//  Created by Stanislav Korotaev on 3/2/14.
//
//

#include "ResultsLayer.h"


ResultsLayer::ResultsLayer(Game::Type gameType, int playerID)
{
    button1->setVisible(false);
    
    setupLabel(gameType, playerID);
}

void ResultsLayer::setupLabel(Game::Type gameType, int playerID)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    
    CCLabelTTF* label = CCLabelTTF::create(getText(gameType, playerID).c_str(), default_font.c_str(), 64);
	label->setPosition(ccp(visibleSize.width/2, menu->getPositionY() + button1->getPositionY()));
    
	this->addChild(label);
}

std::string ResultsLayer::getText(Game::Type gameType, int playerID)
{
    if(gameType == Game::VS_AI){
        if(playerID){
            return "AI WINS!";
        }else{
            return "PLAYER WINS!";
        }
        
    }else if(gameType == Game::VS_HUMAN){
        if(playerID){
            return "PLAYER 2 WINS!";
        }else{
            return "PLAYER 1 WINS!";
        }
    }
}