#pragma once

class MusicPlayer{
public:
    static void playMenuMusic();
    static void playBattleMusic();
    // static void playLastBossMusic(); // for Ender
    
private:
    MusicPlayer();
    
    static const char* getRandomBattleMusic();
};