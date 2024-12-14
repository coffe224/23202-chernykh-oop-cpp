#include <string>
#include <fstream>

#include "Sample.h"

class WavFile
{
    private:
        std::string fileName;
        std::fstream file;

        std::uint16_t getSampleValue();
        void setSampleValue(std::uint16_t value);
        
    public:
        WavFile(std::string filename);
        void open();
        bool isOpen();
        bool isEOF();
        void close();

        void seek(int sample_index);
        int tell();
        void next();
        Sample get();
        void set(Sample sample);
        
        int start_position;
        int sample_rate;
        int samples;
};