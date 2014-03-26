#pragma once

#include "Button.h"
#include "Difficulty.h"
#include <string>


class AIButton : public Button{
public:
    AIButton(const std::string& rank, const std::string& name, Difficulty::Type difficulty, Handler* handler, int priority = -255);

private:
    std::string rank;
    std::string name;
    Difficulty::Type difficulty;
    
    cocos2d::CCSprite* getInactive();
    cocos2d::CCSprite* getActive();
    
    cocos2d::CCLabelTTF* createRank(const std::string& rank);
    cocos2d::CCLabelTTF* createName(const std::string& name);
    cocos2d::CCLabelTTF* createDifficulty(Difficulty::Type difficulty);
};