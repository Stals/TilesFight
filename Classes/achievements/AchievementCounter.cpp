#include "AchievementCounter.h"
#include "AchievementChecker.h"

#define COUNTERS_XML "counters.xml"

CounterContainer::CounterContainer()
{
    counters = new SettingsXML(COUNTERS_XML);
}

CounterContainer* CounterContainer::current()
{
    static CounterContainer container;
    return &container;
}

void CounterContainer::incrementCounter(const std::string& name, int amount)
{
    const int prevAmount = getCounterAmount(name);
    setValue(name, prevAmount + amount);
}

void CounterContainer::setIfBigger(const std::string& name, int amount)
{
    const int prevAmount = getCounterAmount(name);

    if(prevAmount > amount){
        setValue(name, amount);
    }
}

void CounterContainer::setValue(const std::string& counterName, int amount)
{
    counters->setValue(counterName, amount);
    counters->save();
    
    AchievementChecker::current()->checkCounterAcievements(counterName, amount);
}


int CounterContainer::getCounterAmount(const std::string& name)
{
    return counters->getInt(name, 0);
}
