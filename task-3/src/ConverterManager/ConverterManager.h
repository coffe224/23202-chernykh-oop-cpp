#include "ConverterWrapper.h"

class ConverterManager
{
    public:
        ConverterManager();
        ConverterWrapper* getConverter(std::vector<std::string> command);

    private:
        std::map<std::string, ConverterWrapperFactory*> factories;
};