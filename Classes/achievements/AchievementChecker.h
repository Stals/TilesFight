#pragma once

#include <string>
#include <map>

#include "../../lib/thirdparty/pugi/pugixml.hpp"


struct Achievement{
    Achievement(pugi::xml_node node);
    
    std::string counterName;
    int value;
    std::string id;
};

class AchievementChecker{
public:
    ~AchievementChecker();
    static AchievementChecker* current();
    void checkCounterAcievements(const std::string& counterName, int amount);
    
private:
    AchievementChecker();
    void parseAchievements();
    void postAchievement(const std::string& id, int percent);
    
    pugi::xml_document doc;
    typedef std::multimap<std::string, Achievement*> AchievementsContainer;
    AchievementsContainer achievements;
};
