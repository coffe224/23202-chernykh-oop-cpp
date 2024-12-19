#include "ConverterManager.h"

ConverterManager::ConverterManager()
{
    factories = {
        {"mute", new MuteWrapperFactory},
        {"mix", new MixWrapperFactory},
        {"fade", new FadeWrapperFactory},
    };
}

ConverterWrapper* ConverterManager::getConverter(std::vector<std::string> command)
{
    auto pos = factories.find(command[0]);
    if (pos == factories.end()) {
        throw;
    } else {
        ConverterWrapperFactory* factory = pos->second;
        return factory->create(command);
    }
}