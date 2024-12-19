#include <string>
#include <vector>

#include "../WavProcessing/WavReader.h"
#include "../ConverterManager/ConverterManager.h"

class Controller
{
    private:
        WavReader wavReader;
        ConverterManager converterManager;

        std::vector<WavFile*> inputWavFiles;
        std::vector<ConverterWrapper*> converters;

        void getConverters(std::string config_filename);
    public:
        void help();
        void start(std::string config_filename, std::string output_filename,
                   std::vector<std::string> input_filenames);
};