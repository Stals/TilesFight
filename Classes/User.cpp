#include "User.h"
#include "../lib/data/SettingsXML.h"
#include "../lib/cocos/sound/Sound.h"

#define SETTINGS_FILE "settings.xml"

#define TAG_MUSIC_ENABLED "MusicEnabled"
#define TAG_EFFECTS_ENABLED "EffectsEnabled"

#define TAG_VSHUMAN_COLOR1 "VSHumanColor1"
#define TAG_VSHUMAN_COLOR2 "VSHumanColor2"
#define TAG_VSAI_COLOR "VSAIColor"

User* User::instance = 0;

User::User()
{
    settings = new SettingsXML(SETTINGS_FILE);
}

User* User::current()
{
    if(!instance){
        instance = new User;
    }
    
    return instance;
}

void User::init()
{
    Sound::setMusicEnabled(isMusicEnabled());
    Sound::setEffectVolume(isEffectsEnabled());
}

void User::setValue(const std::string& key, bool value)
{
    settings->setValue(key, value);
    settings->save();
}

void User::setValue(const std::string& key, int value)
{
    settings->setValue(key, value);
    settings->save();
}


bool User::isMusicEnabled()
{
    return settings->getBool(TAG_MUSIC_ENABLED, true);
}

bool User::isEffectsEnabled()
{
    return settings->getBool(TAG_EFFECTS_ENABLED, true);
}

void User::setMusicEnable(bool enabled)
{
    setValue(TAG_MUSIC_ENABLED, enabled);
}

void User::setEffectsEnable(bool enabled)
{
    setValue(TAG_EFFECTS_ENABLED, enabled);
}



// COLORS
#define TAG_VSHUMAN_COLOR1 "VSHumanColor1"
#define TAG_VSHUMAN_COLOR2 "VSHumanColor2"
#define TAG_VSAI_COLOR "VSAIColor"
int User::getVSHumanColor1()
{
    return settings->getInt(TAG_VSHUMAN_COLOR1, 0);
}

int User::getVSHumanColor2()
{
    return settings->getInt(TAG_VSHUMAN_COLOR2, 1);
}

int User::getVSAIColor()
{
    return settings->getInt(TAG_VSAI_COLOR, 0);
}

void User::setVSHumanColor1(int index)
{
    setValue(TAG_VSHUMAN_COLOR1, index);
}

void User::setVSHumanColor2(int index)
{
    setValue(TAG_VSHUMAN_COLOR2, index);
}

void User::setVSAIColor(int index)
{
    setValue(TAG_VSAI_COLOR, index);
}
