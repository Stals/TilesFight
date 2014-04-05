#include "EffectPlayer.h"

#include "SimpleAudioEngine.h"
#include "RandomGenerator.h"
#include "Constants.h"

#define ENGINE CocosDenshion::SimpleAudioEngine::sharedEngine()

void EffectPlayer::playSelectionEffect()
{
    playEffect(SOUND("select1.wav"), false, RandomGenerator::getRandomDouble(0.9, 1.05), 0.7f);
}

void EffectPlayer::playAttackEffect()
{
    playEffect(SOUND("pew2.wav"), false, RandomGenerator::getRandomDouble(1.2, 1.7), 1.0f);
    
    // в теории можно использовать для больших армий
    //playEffect(SOUND("pew4.wav"), false, RandomGenerator::getRandomDouble(1.0, 1.1), 0.7f);

}

void EffectPlayer::playShakeEffect()
{
    
}

void EffectPlayer::playerDoorEffect()
{
    playEffect(SOUND("door.wav"), false, RandomGenerator::getRandomDouble(1.0, 1.1), 0.225f);
}

void EffectPlayer::playEffect(const std::string& filename, bool loop, float pitch, float gain)
{
    //ENGINE->playEffect(filename.c_str(), loop, pitch, 0.0f, gain);
}
