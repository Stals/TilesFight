//
//  ResultsLayer.cpp
//  HelloCpp
//
//  Created by Stanislav Korotaev on 3/2/14.
//
//

#include "ResultsLayer.h"


ResultsLayer::ResultsLayer(Player* winner)
{
    button1->setVisible(false);
    
    setupLabel(winner);
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