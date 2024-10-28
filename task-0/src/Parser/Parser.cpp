#include "Parser.h"
#include <iostream>

std::list<std::string> Parser::getWords(std::string& line)
{
    std::list<std::string> parsed_words;

    wordStartIt = line.begin();
    wordEndIt = line.begin();
    lineEndIt = line.end();

    while (wordStartIt != lineEndIt) {
        findWordStart();
        findWordEnd();

        if (wordStartIt != lineEndIt) {
            std::string word(wordStartIt, wordEndIt);
            lowerWord(word);
            parsed_words.push_back(word);
        }
    }

    return parsed_words;
}

bool Parser::isDelim(char l)
{
    bool is_delim = !(('a' <= l && l <= 'z') || ('A' <= l && l <= 'Z') ||
                      ('0' <= l && l <= '9'));
    return is_delim;
}

void Parser::lowerWord(std::string& word)
{
    for (std::string::iterator it = word.begin(); it != word.end(); ++it) {
        if ('A' <= *it && *it <= 'Z') {
            *it -= ('A' - 'a');
        }
    }
}

void Parser::findWordStart()
{
    wordStartIt = wordEndIt;
    while (isDelim(*wordStartIt) && wordStartIt != lineEndIt) {
        wordStartIt++;
    }
}

void Parser::findWordEnd()
{
    wordEndIt = wordStartIt;
    while (!isDelim(*wordEndIt) && wordEndIt != lineEndIt) {
        wordEndIt++;
    }
}
