#include "WavReader.h"
#include <iostream>

WavFile WavReader::read(std::string filename)
{
    byteReader.open(filename);

    std::size_t size_of_file = byteReader.getFileSize();
    if (size_of_file < 44) {
        std::cerr << "File is only " << size_of_file << " bytes long.\n";
        throw;
    }

    std::string chunk_id = byteReader.getRawString(4);
    if (chunk_id != "RIFF") {
        std::cerr << "File specification is " << chunk_id
                  << " instead of RIFF.\n";
        throw;
    }

    std::uint32_t chunk_size = byteReader.getU32LE();
    std::uint32_t expected_chunk_size = size_of_file - 8;
    if (chunk_size != expected_chunk_size) {
        std::cerr << "Chunk size differs from expected size.\n";
        std::cerr << chunk_size << " != " << expected_chunk_size << "\n";
        throw;
    }

    std::string format = byteReader.getRawString(4);
    if (format != "WAVE") {
        std::cerr << "File format is " << format << " instead of WAVE.\n";
        throw;
    }

    std::string subchunk1_id = byteReader.getRawString(4);
    if (subchunk1_id != "fmt ") {
        std::cerr << "Subchunk ID is " << subchunk1_id
                  << " instead of 'fmt '\n";
        throw;
    }

    std::uint32_t subchunk1_size = byteReader.getU32LE();
    if (subchunk1_size != 16) {
        std::cerr << "Subchunk size is " << subchunk1_size
                  << " bytes instead 16.\n";
        throw;
    }

    std::uint16_t audio_format = byteReader.getU16LE();
    if (audio_format != 1) {
        std::cerr << "Unsupported audio format.\n";
        throw;
    }

    std::uint16_t num_of_channels = byteReader.getU16LE();
    if (num_of_channels != 1) {
        std::cerr << "Unsupported number of channels.\n";
        throw;
    }

    std::uint32_t sample_rate = byteReader.getU32LE();
    if (sample_rate != 44100) {
        std::cerr << "Unsupported sample rate.\n";
        throw;
    }

    std::uint32_t byte_rate = byteReader.getU32LE();
    std::uint16_t block_align = byteReader.getU16LE();
    std::uint16_t bits_per_sample = byteReader.getU16LE();

    if (bits_per_sample != 16) {
        std::cerr << "Unsupported bits per sample.\n";
        throw;
    }

    std::uint32_t expected_byte_rate =
        sample_rate * num_of_channels * (bits_per_sample / 8);
    if (byte_rate != expected_byte_rate) {
        std::cerr << "Byte rate differs from expected byte rate.\n";
        std::cerr << byte_rate << " != " << expected_byte_rate << "\n";
        throw;
    }

    std::uint16_t expected_block_align =
        num_of_channels * (bits_per_sample / 8);
    if (block_align != expected_block_align) {
        std::cerr << "Block align differs from expected block align.\n";
        std::cerr << block_align << " != " << expected_block_align << "\n";
        throw;
    }

    std::uint32_t num_of_samples =
        (size_of_file - 44) / (num_of_channels * (bits_per_sample / 8));

    std::string subchunk2_id = byteReader.getRawString(4);
    if (subchunk2_id != "data") {
        std::cerr << "Subchunk ID is '" << subchunk2_id
                  << "' instead of 'data'\n";
        throw;
    }

    std::uint32_t subchunk2_size = byteReader.getU32LE();
    std::uint32_t expected_subchunk2_size =
        num_of_samples * num_of_channels * (bits_per_sample / 8);
    if (subchunk2_size != expected_subchunk2_size) {
        std::cerr << "Data size differs from expected data size.\n";
        std::cerr << subchunk2_size << " != " << expected_subchunk2_size << "\n";
        throw;
    }

    WavFile wavFile(filename);
    wavFile.start_position = 44;
    wavFile.sample_rate = sample_rate;
    wavFile.samples = num_of_samples;


    return wavFile;
}

