#include "AppDelegate.h"

#include <vector>
#include <string>

#include "Constants.h"
#include "GameLayer.h"
#include "TitleScreen.h"
#include "Game.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	srand (time(NULL));

    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);

    // Set the design resolution
    pEGLView->setDesignResolutionSize(1024, 768, kResolutionNoBorder);
    //pEGLView->setDesignResolutionSize(1136, 640, kResolutionNoBorder);

    CCSize frameSize = pEGLView->getFrameSize();
    
    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    Game::current().setArtScale(0.5);

    CCScene *pScene = TitleScreen::scene();
    CCDirector::sharedDirector()->runWithScene(pScene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    //SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    
    if(Game::current().getCurrentScreen() == Game::GAME_SCREEN){
        Game::current().pauseGame();
    }
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    //SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::preloadSounds(){
	/*CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0f);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/win.wav");*/
}

