#include "ColorPicker.h"

#include "Hexagon.h"
#include "Player.h"

#define HEX_SIZE 100

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

void ColorPicker::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it){
		CCTouch* touch = ((CCTouch*)*it);
        
        for(size_t i = 0; i < hexagons.size(); ++i){
            Hexagon* hex = hexagons[i];
            hex->setSelected(false);
            if(hex->containsTouchLocation(touch)){
                hex->setSelected(true);
            }
        }
    }
}

void ColorPicker::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    
}

void ColorPicker::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
}

void ColorPicker::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    
}

