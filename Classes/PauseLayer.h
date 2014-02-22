#pragma once

#include "Constants.h"

class PauseLayer : public CCLayer{
public:
	PauseLayer();
    
private:
	void setupBackground();
    void setupButtons();
    
    void resumeChosen(CCObject* pSender);
    void restartChosen(CCObject* pSender);
	void menuChosen(CCObject* pSender);
};