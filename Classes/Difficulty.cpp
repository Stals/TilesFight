#include "Difficulty.h"
#include "Constants.h"

std::string Difficulty::getDifficultyText(Type difficulty)
{
    switch (difficulty) {
        case Easy:
            return "EASY";
        case Normal:
            return "NORMAL";
        case Hard:
            return "HARD";
        case VeryHard:
            return "VERY HARD";
        case Impossible:
            return "IMPOSSIBLE";
        case Legendary:
            return "LEGENDARY";
        default:
            return "Unknown Difficulty";
    }
}

cocos2d::ccColor3B Difficulty::getDifficultyColor(Type difficulty)
{
    switch (difficulty) {
        case Easy:
            return hexGreen;
        case Normal:
            return hexLightBlue;
        case Hard:
            return hexOrange;
        case VeryHard:
            return hexRed;
        case Impossible:
            return hexPurple;
        case Legendary:
            return hexBrown;
        default:
            return hexGray;
    }
}