#pragma once

#include <vector>
#include <string>

class StringParser
{
    public:
        std::vector<std::string> getWords(std::string& line, const char delim = ' ');

    private:
        char delim;

        std::string::iterator wordStartIt;
        std::string::iterator wordEndIt;
        std::string::iterator lineEndIt;

        bool isDelim(char l);
        void findWordStart();
        void findWordEnd();
};