#include "Controller.h"

void Controller::start(std::string config_filename, std::string output_filename, std::vector<std::string> input_filenames)
{
    for (auto input_filename : input_filenames) {
        WavFile wav_file = wavReader.read(input_filename);
        inputWavFiles.push_back(wav_file);
    }

    int num_of_input_files = inputWavFiles.size();
    std::vector<ConverterWrapper*> converter_queue = configParser.parse(config_filename);
    
    // copy_file 

    WavFile output_wav_file;
    
    for (auto wrapper : converter_queue) {
        std::vector<int> request_wav_files = (*wrapper).requestWavFiles();
        std::vector<WavFile> requested_files = {};

        (*wrapper).convert(output_wav_file, requested_files);
    }
}