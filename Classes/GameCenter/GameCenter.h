#pragma once

class GameCenter
{
public:
    void login();
    
    bool showAchievements();
    void postAchievement(const char* idName, int percentComplete);
    void clearAllAchievements();
    
    bool showScores();
    void postScore(const char* idName, int score);
    void clearAllScores();

/*
#if AVALON_PLATFORM_IS_ANDROID_GOOGLE
    void signIn();
    void signOut();
    bool isSignedIn();
#endif
*/
};

