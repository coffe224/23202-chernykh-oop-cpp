#include "StringParser.h"

std::vector<std::string> StringParser::getWords(std::string& line, const char delimeter)
{
    delim = delimeter;
    std::vector<std::string> parsed_words;

    wordStartIt = line.begin();
    wordEndIt = line.begin();
    lineEndIt = line.end();

    while (wordStartIt != lineEndIt) {
        findWordStart();
        findWordEnd();

        if (wordStartIt != lineEndIt) {
            std::string word(wordStartIt, wordEndIt);
            parsed_words.push_back(word);
        }
    }

    return parsed_words;
}

bool StringParser::isDelim(char l)
{
    return l == delim;
}

void StringParser::findWordStart()
{
    wordStartIt = wordEndIt;
    while (isDelim(*wordStartIt) && wordStartIt != lineEndIt) {
        wordStartIt++;
    }
}

void StringParser::findWordEnd()
{
    wordEndIt = wordStartIt;
    while (!isDelim(*wordEndIt) && wordEndIt != lineEndIt) {
        wordEndIt++;
    }
}