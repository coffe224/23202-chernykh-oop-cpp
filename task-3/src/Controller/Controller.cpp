#include <iostream>

#include "../ConfigParser/ConfigParser.h"
#include "Controller.h"

void Controller::start(std::string config_filename, std::string output_filename,
                       std::vector<std::string> input_filenames)
{
    for (auto input_filename : input_filenames) {
        WavFile* wav_file = wavReader.read(input_filename);
        inputWavFiles.push_back(wav_file);
    }

    int num_files = inputWavFiles.size();

    getConverters(config_filename);
    std::cout << converters.size() << "\n";

    WavFile* output_wav_file = new WavFile(inputWavFiles[0], output_filename);

    for (auto converter : converters) {
        std::vector<int> files_request = converter->requestWavFiles();
        std::vector<WavFile*> requested_files = getRequest(files_request);

        converter->convert(output_wav_file, requested_files);
    }

    // delete 
}

void Controller::getConverters(std::string config_filename)
{
    ConfigParser config_parser(config_filename);
    while (true) {
        std::vector<std::string> command = config_parser.getCommand();
        if (command.empty()) {
            break;
        }
        ConverterWrapper* converter = converterManager.getConverter(command);
        converters.push_back(converter);
    }
}