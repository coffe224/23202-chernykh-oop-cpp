#include "Parser.h"
#include <iostream>

void Parser::parseLine(std::string& line, std::list<std::string>& parsed_list) {
    wordStartIt = line.begin();
    wordEndIt = line.begin();
    lineEndIt = line.end();

    while (wordStartIt != lineEndIt) {
        findWordStart();
        findWordEnd();

        if (wordStartIt != lineEndIt) {
            parsed_list.push_back(std::string(wordStartIt, wordEndIt));
        }
    } 

}

bool Parser::isDelim(char l) {
    bool is_delim = !(('a' <= l && l <= 'z') || ('A' <= l && l <= 'Z') || ('0' <= l && l <= '9'));
    return is_delim;
}

void Parser::findWordStart() {
    wordStartIt = wordEndIt;
    while (isDelim(*wordStartIt) && wordStartIt != lineEndIt) {
        wordStartIt++;
    }            
}

void Parser::findWordEnd() {
    wordEndIt = wordStartIt;
    while (!isDelim(*wordEndIt) && wordEndIt != lineEndIt) {
        wordEndIt++;
    }
}
