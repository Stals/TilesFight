//
//  VsAIScreen.cpp
//  HelloCpp
//
//  Created by Stanislav Korotaev on 3/10/14.
//
//
#include "TBAScreen.h"
#include "Constants.h"


#define FONT_SIZE 48.f



TBAScreen::TBAScreen()
{
    setupLabels();
}


void TBAScreen::setupLabels()
{
    CCLabelTTF* label = CCLabelTTF::create("TO BE ADDED...", default_font.c_str(), FONT_SIZE);

    addChild(label);
}
