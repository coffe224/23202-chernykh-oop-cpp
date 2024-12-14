#pragma once

#include <cstdint>

class Sample {
    private:
        bool is_empty;
        std::int16_t value;

    public:
        Sample();
        bool isEmpty();
        void setEmpty();

        std::int16_t getValue();
        void setValue(std::int16_t);
};