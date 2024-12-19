#include "Converter.h"

class ConverterFactory
{
        public:
            virtual Converter* create(std::vector<int> params = {}) = 0;
};

class SilencerFactory : public ConverterFactory
{
        public:
            Converter* create(std::vector<int> params = {});
};

class MixerFactory : public ConverterFactory
{
        public:
            Converter* create(std::vector<int> params = {});
};

class FaderFactory : public ConverterFactory
{
        public:
            Converter* create(std::vector<int> params = {});
};