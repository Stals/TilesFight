#pragma once

class GameCenter
{
public:
    static void login();
    
    static bool showAchievements();
    static void postAchievement(const char* idName, int percentComplete);
    static void clearAllAchievements();
    
    static bool showScores();
    static void postScore(const char* idName, int score);
    static void clearAllScores();

/*
#if AVALON_PLATFORM_IS_ANDROID_GOOGLE
    void signIn();
    void signOut();
    bool isSignedIn();
#endif
*/
};

