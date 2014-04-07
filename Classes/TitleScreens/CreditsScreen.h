#pragma once

#include "EmptyScreen.h"
#include "Constants.h"

class CreditsScreen : public EmptyScreen
{
public:
    CreditsScreen();
    
private:
    void setupCredits();
    
    CCLabelTTF* createTitle(const std::string& title);
    CCSprite* createPerson(const std::string& name, const std::string& twitterLink = std::string(), const std::string& fbLink = std::string());
    
    void openURL(cocos2d::CCObject* pSender);
};