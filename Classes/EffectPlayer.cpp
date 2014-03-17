#include "EffectPlayer.h"

#include "SimpleAudioEngine.h"
#include "RandomGenerator.h"
#include "Constants.h"

#define ENGINE CocosDenshion::SimpleAudioEngine::sharedEngine()

void EffectPlayer::playSelectionEffect()
{
    playEffect(SOUND("select1.wav"), false, RandomGenerator::getRandomDouble(0.9, 1.1), 1.0f);
}

void EffectPlayer::playAttackEffect()
{
    //playEffect(SOUND("pew.wav"), false, RandomGenerator::getRandomDouble(1, 2.0), 0.5f);

}

void EffectPlayer::playShakeEffect()
{
    
}

void EffectPlayer::playEffect(const std::string& filename, bool loop, float pitch, float gain)
{
    ENGINE->playEffect(filename.c_str(), loop, pitch, 0.0f, gain);
}
