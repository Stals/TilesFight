#include "AIButton.h"

#include "Constants.h"
using namespace cocos2d;

#define PADDING 16

#define FONT_DIFFICULTY 14
#define FONT_NAME 14
#define FONT_RANK 14

AIButton::AIButton(const std::string& rank, const std::string& name, Difficulty::Type difficulty, Handler* handler, int priority)
{
    this->rank = rank;
    this->name = name;
    this->difficulty = difficulty;
    
    this->init(getInactive(), getActive(), handler, priority);
}

CCSprite* AIButton::getInactive()
{
    CCSprite* sprite = CCSprite::create();
    
    CCSprite* glow = CCSprite::create(IMG("glow_dark.png"));
    glow->setVisible(false);
    
    sprite->addChild(glow);
    
    cocos2d::CCLabelTTF* rankLabel = createRank(rank);
    cocos2d::CCLabelTTF* nameLabel = createName(name);
    cocos2d::CCLabelTTF* difficultyLabel = createDifficulty(difficulty);
    
    float maxWidth = std::max(std::max(rankLabel->getContentSize().width, nameLabel->getContentSize().width), difficultyLabel->getContentSize().width);
    CCSize contentSize = CCSizeMake(maxWidth, FONT_DIFFICULTY + FONT_NAME + FONT_RANK);
    sprite->setContentSize(contentSize);
    
    glow->setPositionY(contentSize.height/2 + 10);
    rankLabel->setPositionY(contentSize.height/2 + PADDING);
    nameLabel->setPositionY(contentSize.height/2);
    difficultyLabel->setPositionY(contentSize.height/2 -PADDING);
    
    glow->setPositionX(contentSize.width/2);
    rankLabel->setPositionX(contentSize.width/2);
    nameLabel->setPositionX(contentSize.width/2);
    difficultyLabel->setPositionX(contentSize.width/2);
    
    sprite->addChild(rankLabel);
    sprite->addChild(nameLabel);
    sprite->addChild(difficultyLabel);

    return sprite;
}

CCSprite* AIButton::getActive()
{
    CCSprite* sprite = CCSprite::create();
    
    CCSprite* glow = CCSprite::create(IMG("glow_dark.png"));
    //glow->setVisible(false);
    
    sprite->addChild(glow);

    
    cocos2d::CCLabelTTF* rankLabel = createRank(rank);
    cocos2d::CCLabelTTF* nameLabel = createName(name);
    cocos2d::CCLabelTTF* difficultyLabel = createDifficulty(difficulty);
    
    float maxWidth = std::max(std::max(rankLabel->getContentSize().width, nameLabel->getContentSize().width), difficultyLabel->getContentSize().width);
    CCSize contentSize = CCSizeMake(maxWidth, FONT_DIFFICULTY + FONT_NAME + FONT_RANK);
    sprite->setContentSize(contentSize);
    
    glow->setPositionY(contentSize.height/2 + 10);
    rankLabel->setPositionY(contentSize.height/2 + PADDING);
    nameLabel->setPositionY(contentSize.height/2);
    difficultyLabel->setPositionY(contentSize.height/2 -PADDING);
    
    glow->setPositionX(contentSize.width/2);
    rankLabel->setPositionX(contentSize.width/2);
    nameLabel->setPositionX(contentSize.width/2);
    difficultyLabel->setPositionX(contentSize.width/2);
    
    sprite->addChild(rankLabel);
    sprite->addChild(nameLabel);
    sprite->addChild(difficultyLabel);
    
    return sprite;
}


cocos2d::CCLabelTTF* AIButton::createRank(const std::string& rank)
{
    return CCLabelTTF::create(rank.c_str(), default_font.c_str(), FONT_RANK);
}

cocos2d::CCLabelTTF* AIButton::createName(const std::string& name)
{
    return CCLabelTTF::create(name.c_str(), default_font.c_str(), FONT_NAME);
}

cocos2d::CCLabelTTF* AIButton::createDifficulty(Difficulty::Type difficulty)
{
    CCLabelTTF* label = CCLabelTTF::create(Difficulty::getDifficultyText(difficulty).c_str() , default_font.c_str(), FONT_DIFFICULTY);
    label->setColor(Difficulty::getDifficultyColor(difficulty));
    return label;
}