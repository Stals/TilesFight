#pragma once

#include "Constants.h"

class TitleScreen : public CCLayer{
public:
	~TitleScreen();
	virtual bool init();
	static cocos2d::CCScene* scene();
    
private:
	CREATE_FUNC(TitleScreen);
    
	void setupBackground();
	void setupButtons();
    
	void vsAIChosen(CCObject* pSender);
    void vsHumanChosen(CCObject* pSender);
	void tutorialChosen(CCObject* pSender);
	void gamecenterChosen(CCObject* pSender);
	void settingsChosen(CCObject* pSender);
	void creditsChosen(CCObject* pSender);


};