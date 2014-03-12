#include "ColorPicker.h"

#include "Hexagon.h"
#include "Player.h"

#define HEX_SIZE 90

#define WIDTH 3
#define HEIGHT 3

ColorPicker::ColorPicker()
{
    CCLayer::init();
    autorelease();
    setTouchEnabled(true);

    owner = new Player("Color_Picker", hexRed);
    
    setupColors();
    
    
    this->setContentSize(CCSizeMake(HEX_SIZE * WIDTH, HEX_SIZE * HEIGHT));
    setupHexagons();
}

ColorPicker::~ColorPicker()
{
    if(owner) delete owner;
}

void ColorPicker::setupColors()
{
    colors.push_back(hexRed);
    colors.push_back(hexGreen);
    colors.push_back(hexOrange);
    colors.push_back(hexLightBlue);
    colors.push_back(hexPurple);
    colors.push_back(hexCyan);
    colors.push_back(hexBrown);
}

void ColorPicker::setupHexagons()
{
    const float shiftX = HEX_SIZE / 2;
    const float shiftY = HEX_SIZE * 3/4;
    
    size_t colorID = 0;
    for(size_t y = 0; y < HEIGHT; ++y){
        const size_t maxX = (y == 1) ? WIDTH : WIDTH-1;
        for(size_t x = 0; x < maxX; ++x){
    
            Hexagon* hex = new Hexagon(x, y);
            hex->setScale(HEX_SIZE / hex->getContentSize().width);
            
            if((y % 2) == 0){
                hex->setPositionX(x * scaledWidth(hex) - shiftX);
            }else{
                hex->setPositionX((x * scaledWidth(hex)) - (scaledWidth(hex) / 2) - shiftX);
            }
            hex->setPositionY(y * (scaledHeight(hex) * 3/4) - shiftY);
            
            hex->changeOwner(owner);
            hex->setColor(colors[colorID]);
            this->addChild(hex);
            hexagons.push_back(hex);
            
            ++colorID;
        }
    }
}

bool ColorPicker::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    for(size_t i = 0; i < hexagons.size(); ++i){
        Hexagon* hex = hexagons[i];
        if(hex->containsTouchLocation(pTouch)){
            deselectAll();
            hex->setSelected(true);
            return true;
        }
    }
    
    return false;
}

void ColorPicker::deselectAll()
{
    for(size_t i = 0; i < hexagons.size(); ++i){
        hexagons[i]->setSelected(false);
    }
}

void ColorPicker::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void ColorPicker::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void ColorPicker::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}


void ColorPicker::pickAtIndex(size_t index)
{
    for(size_t i = 0; i < hexagons.size(); ++i){
        Hexagon* hex = hexagons[i];
        
        if(i == index){
            hex->setSelected(true);
        }else{
            hex->setSelected(false);
        }
    }
}

void ColorPicker::onEnter(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -262, true);
    CCLayer::onEnter();
}

void ColorPicker::onExit(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

ccColor3B ColorPicker::getSelectedColor()
{
    for(size_t i = 0; i < hexagons.size(); ++i){
        Hexagon* hex = hexagons[i];
        if(hex->isSelected()){
            return hex->getColor();
        }
    }
    
    return hexDark;
}

