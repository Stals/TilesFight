//
//  MusicPlayer.cpp
//  HelloCpp
//
//  Created by Stanislav Korotaev on 3/15/14.
//
//

#include "MusicPlayer.h"
#include "../lib/cocos/sound/Sound.h"
#include "Constants.h"
#include "../lib/utils/RandomGenerator.h"



const char* battleMusic[] = {
    "buildy.mp3",
    "n-Dimensions (Main Theme)_0.mp3",
    "Orbital Colossus_0.mp3",
    "Red Doors 2.0 (GameClosure Edition)_0.mp3",
    "Tactical Pursuit_0.mp3",
    "Thrust Sequence_0.mp3",
    "Vilified (2012)_0.mp3"

};

void MusicPlayer::playMenuMusic()
{
    Sound::playMusic(MUSIC("mainmenu.mp3"), true);
}

void MusicPlayer::playBattleMusic()
{
    Sound::playMusic(MUSIC(getRandomBattleMusic()), true);
}

const char* MusicPlayer::getRandomBattleMusic()
{
    const size_t size = sizeof(battleMusic) / sizeof(const char*);
    return battleMusic[RandomGenerator::getRandom(0, size)];
}
