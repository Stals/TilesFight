#pragma once
#include "cocos2d.h"

struct Difficulty{
    enum Type{
        Easy = 0,
        Normal,
        Hard,
        VeryHard,
        Impossible,
        Legendary
    };
    
    static std::string getDifficultyText(Type difficulty);
    static cocos2d::ccColor3B getDifficultyColor(Type difficulty);
};
