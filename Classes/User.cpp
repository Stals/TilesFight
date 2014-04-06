#include "User.h"
#include "../lib/data/SettingsXML.h"

#define SETTINGS_FILE "settings.xml"

#define TAG_MUSIC_ENABLED "MusicEnabled"
#define TAG_EFFECTS_ENABLED "EffectsEnabled"

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

void User::setValue(const std::string& key, bool value)
{
    settings->setValue(key, value);
    settings->save();
}
