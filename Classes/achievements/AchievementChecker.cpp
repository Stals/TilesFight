#include "AchievementChecker.h"

#include "../../lib/data/FileUtils.h"
#include "GameCenter/GameCenter.h"

#define ACHIEVEMENTS_XML "achievements.xml"



Achievement::Achievement(pugi::xml_node node)
{
    counterName = node.attribute("Counter").as_string();
    value = node.attribute("Value").as_int();
    id = node.attribute("id").as_string();
}

// ----------------------------------------------------------------

AchievementChecker::AchievementChecker()
{
    bool success = doc.load_file(FileUtils::getResoursePath(ACHIEVEMENTS_XML).c_str());
    parseAchievements();
}

AchievementChecker* AchievementChecker::current()
{
    static AchievementChecker checker;
    return &checker;
}

AchievementChecker::~AchievementChecker()
{
    // TODO delete all achievements from map
}

void AchievementChecker::parseAchievements()
{
    pugi::xml_node achievementsNode = doc.child("Achievements");
    
    for(pugi::xml_node_iterator it = achievementsNode.begin(); it != achievementsNode.end(); ++it){
        Achievement* achievement = new Achievement(*it);
        achievements.insert(std::make_pair(achievement->counterName, achievement));
    }
}

void AchievementChecker::checkCounterAcievements(const std::string& counterName, int amount)
{
    if(amount == 0) return;
    
    std::pair<AchievementsContainer::iterator, AchievementsContainer::iterator> p = achievements.equal_range(counterName);
    
    for(AchievementsContainer::iterator it = p.first; it != p.second; ++it)
    {
        Achievement* achievement = it->second;
        postAchievement(achievement->id, (amount / (float)achievement->value) * 100);
    }
}

void AchievementChecker::postAchievement(const std::string& id, int percent)
{
    if(percent > 100) percent = 100;
    GameCenter::postAchievement(id.c_str(), percent);
}

