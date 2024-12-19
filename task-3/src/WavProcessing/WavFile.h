#include <string>
#include <fstream>

#include "Sample.h"

class WavFile
{
    private:
        std::string fileName;
        std::fstream file;
        std::size_t index = 0;

        std::int16_t getSampleValue();
        void setSampleValue(std::int16_t value);
        
    public:
        WavFile(std::string filename);
        WavFile(WavFile* wav_file, std::string filename);

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