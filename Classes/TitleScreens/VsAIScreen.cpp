//
//  VsAIScreen.cpp
//  HelloCpp
//
//  Created by Stanislav Korotaev on 3/10/14.
//
//

#include "VsAIScreen.h"
#include "../ColorPicker.h"

VsAIScreen::VsAIScreen()
{
    this->addChild(new ColorPicker);
}