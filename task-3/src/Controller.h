#include <string>
#include <vector>

#include "WavReader.h"
#include "ConfigFileParser.h"

class Controller
{
    private:
        WavReader wavReader;
        ConfigFileParser configParser;

        std::vector<WavFile> inputWavFiles;

    public:
        void help();
        void start(std::string config_filename, std::string output_filename,
                   std::vector<std::string> input_filenames);
};