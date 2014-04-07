//
//  ButtonFactory.cpp
//  SampleGame
//
//  Created by Stanislav Korotaev on 2/16/14.
//  Copyright (c) 2014 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "ButtonFactory.h"
#include "Game.h"

#define MAIN_BUTTON_IMAGE IMG("button.png")
#define ICON_PADDING 15
#define LABEL_PADDING 20


CCSprite* ButtonFactory::mainMenuButtonSprite(const char* iconPath, const std::string& text, IconSide side)
{
    CCSprite *button = CCSprite::create(MAIN_BUTTON_IMAGE);
    button->setAnchorPoint(ccp(0.5, 0.5));
    button->setScale(Game::current().artScale());
    
    CCSprite* icon = CCSprite::create(iconPath);
    icon->setAnchorPoint(ccp(0.5, 0.5));
    button->addChild(icon);

    
    if(side == ICON_RIGHT){
        icon->setPositionX((button->getContentSize().width) - (icon->getContentSize().width) - ICON_PADDING);
    }else{
        icon->setPositionX((icon->getContentSize().width) + ICON_PADDING);
    }
    
    icon->setPositionY(button->getContentSize().height/2);
    
    
    CCLabelTTF* label = CCLabelTTF::create(text.c_str(), default_font.c_str(), 24);
    label->setAnchorPoint(ccp(0.5, 0.5));

	button->addChild(label);
    
    if(side == ICON_RIGHT){
        label->setPositionX((button->getContentSize().width/2) - LABEL_PADDING);
    }else{
        label->setPositionX((button->getContentSize().width/2) + LABEL_PADDING);
    }
    
    label->setPositionY(button->getContentSize().height/2);
    return button;
}

CCSprite* ButtonFactory::buttonSprite(const std::string& text)
{
    CCSprite *button = CCSprite::create(MAIN_BUTTON_IMAGE);
    button->setAnchorPoint(ccp(0.5, 0.5));
    button->setScale(Game::current().artScale());
    
    CCLabelTTF* label = CCLabelTTF::create(text.c_str(), default_font.c_str(), 48);
    label->setAnchorPoint(ccp(0.5, 0.5));
    label->setPositionX((button->getContentSize().width/2));
    label->setPositionY(button->getContentSize().height/2);
    
    button->addChild(label);
    
    return button;
}

Button* ButtonFactory::button(const char* iconPath, const std::string& text, IconSide side, Handler* handler, int touchPrority)
{
    CCSprite* inactive = ButtonFactory::mainMenuButtonSprite(iconPath, text, side);
    CCSprite* pressed = ButtonFactory::mainMenuButtonSprite(iconPath, text, side);
    pressed->setOpacity(127);
    
    Button* button = new Button(inactive, pressed, handler, touchPrority);
    return button;
}


Button* ButtonFactory::button(const std::string& text, Handler* handler, int touchPrority)
{
    CCSprite* inactive = ButtonFactory::buttonSprite(text);
    CCSprite* pressed = ButtonFactory::buttonSprite(text);
    pressed->setOpacity(127);
    
    Button* button = new Button(inactive, pressed, handler, touchPrority);
    return button;
}


Button* ButtonFactory::imageButton(const char* iconPathInactive, const char* iconPathPressed, Handler* handler, int touchPrority)
{
    CCSprite* inactive = CCSprite::create(iconPathInactive);
    CCSprite* pressed = CCSprite::create(iconPathPressed);
    Button* button = new Button(inactive, pressed, handler, touchPrority);
    return button;
}
