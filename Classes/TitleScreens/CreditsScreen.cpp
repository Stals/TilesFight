#include "CreditsScreen.h"

#include "../ButtonFactory.h"
#include "../../lib/cocos/web/WebUtils.h"

#define TWITTER_ICON_INACTIVE IMG("social_twitter.png")
#define TWITTER_ICON_PRESSED TWITTER_ICON_INACTIVE

#define FB_ICON_INACTIVE IMG("social_fb.png")
#define FB_ICON_PRESSED FB_ICON_INACTIVE

#define FONT_SIZE_TITLE 24
#define FONT_SIZE_PERSON 16

#define PADDING_AFTER_TITLE 5
#define PADDING_AFTER_PERSON 25
#define PADDING_PERSON 15
#define PADDING_AFTER_NAME 15

#define BUTTON_PRIORITY -261

CreditsScreen::CreditsScreen()
{
    setupCredits();
}

void CreditsScreen::setupCredits()
{
    const int personNum = 4;
    const int titleNum = 3;
    
    CCLabelTTF* title1 = 0;
    CCLabelTTF* title2 = 0;
    CCLabelTTF* title3 = 0;
    CCSprite* person1 = 0;
    CCSprite* person21 = 0;
    CCSprite* person22 = 0;
    CCSprite* person3 = 0;
    
    title1 = createTitle("PROGRAMMING");
    person1 = createPerson("STANISLAV KOROTAEV", "https://twitter.com/TheBrenor", "https://www.facebook.com/stanislav.korotaev");
    
    title2 = createTitle("MUSIC");
    person21 = createPerson("MATTHEW PABLO  ", "https://twitter.com/matthewpablo", "https://www.facebook.com/pages/Matthew-Pablo/33998389696");
    person22 = createPerson("LANE BECKSTROM", "https://twitter.com/lanebeckstrom", "https://www.facebook.com/lane.beckstrom");
    
    
    title3 = createTitle("BACKGROUNDS");
    person3 = createPerson("RAWDANITSU");
    
    const float totalHeight = title1->getContentSize().height * titleNum + person1->getContentSize().height * personNum + PADDING_AFTER_TITLE * (personNum - 1) + PADDING_AFTER_PERSON * (titleNum - 1);
    
    
    title1->setPositionY(totalHeight / 2 - title1->getContentSize().height / 2);
    person1->setPositionY(title1->getPositionY() - title1->getContentSize().height - PADDING_AFTER_TITLE);
    
    title2->setPositionY(person1->getPositionY() - person1->getContentSize().height - PADDING_AFTER_PERSON);
    person21->setPositionY(title2->getPositionY() - title2->getContentSize().height - PADDING_AFTER_TITLE);
    person22->setPositionY(person21->getPositionY() - person21->getContentSize().height - PADDING_AFTER_TITLE);


    title3->setPositionY(person22->getPositionY() - person22->getContentSize().height - PADDING_AFTER_PERSON);
    person3->setPositionY(title3->getPositionY() - title3->getContentSize().height - PADDING_AFTER_TITLE);
    
    addChild(title1);
    addChild(title2);
    addChild(title3);
    addChild(person1);
    addChild(person21);
    addChild(person22);
    addChild(person3);
}

CCLabelTTF* CreditsScreen::createTitle(const std::string& title)
{
    CCLabelTTF* titleLabel = CCLabelTTF::create(title.c_str(), default_font.c_str(), FONT_SIZE_TITLE);
    return titleLabel;
}

CCSprite* CreditsScreen::createPerson(const std::string& name, const std::string& twitterLink, const std::string& fbLink)
{
    const float iconSize = 32;
    
    bool useTwitter = !twitterLink.empty();
    bool useFB = !fbLink.empty();
    
    CCSprite* person = CCSprite::create();
    
    CCLabelTTF* nameLabel = CCLabelTTF::create(name.c_str(), default_font.c_str(), FONT_SIZE_PERSON);
    nameLabel->setPositionX(nameLabel->getContentSize().width / 2);
    
    float totalWidth = nameLabel->getContentSize().width;
    float totalHeight = MAX(nameLabel->getContentSize().height, iconSize);
    
    if(useTwitter || useFB){
        totalWidth += PADDING_AFTER_NAME;
    }
    
    if(useTwitter){
        totalWidth += iconSize + PADDING_PERSON;
        
        urls.push_back(twitterLink);
        Button* twitterButton = ButtonFactory::imageButton(TWITTER_ICON_INACTIVE, TWITTER_ICON_PRESSED, new Handler(this, callfuncD_selector(CreditsScreen::openURL), (void*)(urls.size() - 1)), BUTTON_PRIORITY);
        twitterButton->setPositionX(nameLabel->getPositionX() + totalWidth - iconSize - nameLabel->getContentSize().width/2);
        twitterButton->setPositionY(totalHeight / 2);

        person->addChild(twitterButton);
    }
    
    if(useFB) {
        totalWidth += iconSize + PADDING_PERSON;

        urls.push_back(fbLink);
        Button* fbButton = ButtonFactory::imageButton(FB_ICON_INACTIVE, FB_ICON_PRESSED, new Handler(this, callfuncD_selector(CreditsScreen::openURL), (void*)(urls.size() - 1)), BUTTON_PRIORITY);
        
        fbButton->setPositionX(nameLabel->getPositionX() + totalWidth - iconSize - nameLabel->getContentSize().width/2);
        fbButton->setPositionY(totalHeight / 2);
        
        person->addChild(fbButton);
    }
    
    person->setContentSize(CCSizeMake(totalWidth, totalHeight));
    nameLabel->setPositionY(totalHeight / 2);
    person->addChild(nameLabel);
    
    return person;
}

void CreditsScreen::openURL(void* data)
{
    const std::string url = urls[(int)data];

    if(!url.empty()){
        WebUtils::openURL(url);
    }
}

float CreditsScreen::getHeight()
{
    return EmptyScreen::getHeight();
}
