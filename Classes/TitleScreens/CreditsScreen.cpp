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
    // TODO add lane guy!
    const int personNum = 3;
    
    CCLabelTTF* title1 = 0;
    CCLabelTTF* title2 = 0;
    CCLabelTTF* title3 = 0;
    CCSprite* person1 = 0;
    CCSprite* person2 = 0;
    CCSprite* person3 = 0;
    
    title1 = createTitle("PROGRAMMING");
    person1 = createPerson("STANISLAV KOROTAEV", "https://twitter.com/TheBrenor", "https://www.facebook.com/stanislav.korotaev");
    
    title2 = createTitle("MUSIC");
    person2 = createPerson("MATTHEW PABLO", "https://twitter.com/matthewpablo", "https://www.facebook.com/pages/Matthew-Pablo/33998389696");
    
    title3 = createTitle("BACKGROUNDS");
    person3 = createPerson("RAWDANITSU");
    
    const float totalHeight = title1->getContentSize().height * personNum + person1->getContentSize().height * personNum + PADDING_AFTER_TITLE * (personNum - 1) + PADDING_AFTER_PERSON * (personNum - 1);
    
    
    title1->setPositionY(totalHeight / 2 - title1->getContentSize().height / 2);
    person1->setPositionY(title1->getPositionY() - title1->getContentSize().height - PADDING_AFTER_TITLE);
    
    title2->setPositionY(person1->getPositionY() - person1->getContentSize().height - PADDING_AFTER_PERSON);
    person2->setPositionY(title2->getPositionY() - title2->getContentSize().height - PADDING_AFTER_TITLE);

    title3->setPositionY(person2->getPositionY() - person2->getContentSize().height - PADDING_AFTER_PERSON);
    person3->setPositionY(title3->getPositionY() - title3->getContentSize().height - PADDING_AFTER_TITLE);
    
    addChild(title1);
    addChild(title2);
    addChild(title3);
    addChild(person1);
    addChild(person2);
    addChild(person3);
}

CCLabelTTF* CreditsScreen::createTitle(const std::string& title)
{
    CCLabelTTF* titleLabel = CCLabelTTF::create(title.c_str(), default_font.c_str(), FONT_SIZE_TITLE);
    return titleLabel;
}

CCSprite* CreditsScreen::createPerson(const std::string& name, const std::string& twitterLink, const std::string& fbLink)
{
    CCSprite* person = CCSprite::create();
    
    CCLabelTTF* nameLabel = CCLabelTTF::create(name.c_str(), default_font.c_str(), FONT_SIZE_PERSON);
    Button* twitterButton = ButtonFactory::imageButton(TWITTER_ICON_INACTIVE, TWITTER_ICON_PRESSED, new Handler(this, menu_selector(CreditsScreen::openURL)), BUTTON_PRIORITY);
    Button* fbButton = ButtonFactory::imageButton(FB_ICON_INACTIVE, FB_ICON_PRESSED, new Handler(this, menu_selector(CreditsScreen::openURL)), BUTTON_PRIORITY);
    
    const float totalWidth = nameLabel->getContentSize().width + PADDING_AFTER_NAME + PADDING_PERSON * 2 + twitterButton->getContentSize().width * 2;
    const float totalHeight = MAX(nameLabel->getContentSize().height, twitterButton->getContentSize().height);
    person->setContentSize(CCSizeMake(totalWidth, totalHeight));
    
    // x
    nameLabel->setPositionX(nameLabel->getContentSize().width / 2);
    twitterButton->setPositionX(nameLabel->getPositionX() + nameLabel->getContentSize().width / 2 + PADDING_PERSON + PADDING_AFTER_NAME);
    fbButton->setPositionX(twitterButton->getPositionX() + twitterButton->getContentSize().width + PADDING_PERSON);
    
    // y
    nameLabel->setPositionY(totalHeight / 2);
    twitterButton->setPositionY(totalHeight / 2);
    fbButton->setPositionY(totalHeight / 2);
    
    person->addChild(nameLabel);
    person->addChild(twitterButton);
    person->addChild(fbButton);
    
    return person;
}

void CreditsScreen::openURL(cocos2d::CCObject* pSender)
{
    WebUtils::openURL("https://twitter.com/TheBrenor");
}
