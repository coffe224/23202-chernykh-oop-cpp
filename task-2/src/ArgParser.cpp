#include "ArgParser.h"

ArgParser::ArgParser() {}

void ArgParser::addOption(char short_name, std::string long_name, bool has_args)
{
    Option option;
    option.shortName = short_name;
    option.longName = long_name;
    option.positional = false;
    option.hasArgs = has_args;
    option.numOfArgs = has_args ? 1 : 0;

    options.push_back(option);
}

void ArgParser::addPosOption(std::string name, int num_of_args)
{
    Option pos_option;
    pos_option.longName = name;
    pos_option.positional = true;
    pos_option.hasArgs = true;
    pos_option.numOfArgs = num_of_args;
    pos_options.push_back(pos_option);
}

void ArgParser::parseArguments(int argc, char const *argv[])
{
    bool isPrevOpt;
    Option prevOpt;
    auto pos_options_it = pos_options.begin();
    int args_pos_options = (*pos_options_it).numOfArgs;

    for (int i = 1; i < argc; i++) {
        std::string word = argv[i];

        if (word.size() > 1 && word[0] == '-' && word[1] != '-') {
            prevOpt = getOpt(word[1]);
            parsed_options.insert_or_assign(prevOpt, "");
            isPrevOpt = true;
        } else if (word.size() > 2 && word[0] == '-' && word[1] == '-') {
            parseLongOpt(word);
            isPrevOpt = false;
        } else if (word[0] != '-') {
            if (isPrevOpt) {
                parsed_options.insert_or_assign(prevOpt, word);
            } else {
                if (args_pos_options == 0) {
                    pos_options_it++;
                    args_pos_options = (*pos_options_it).numOfArgs;
                }
                if (pos_options_it == pos_options.end()) {
                    throw;
                }
                Option pos_opt = (*pos_options_it);
                parsed_pos_options[pos_opt].push_back(word);
                args_pos_options--;
            }
            isPrevOpt = false;
        }
    }
}

ArgParser::Option ArgParser::getOpt(char short_name)
{
    for (auto option : options) {
        if (option.shortName == short_name) {
            return option;
        }
    }
    throw;
}

ArgParser::Option ArgParser::getOpt(std::string long_name)
{
    for (auto option : options) {
        if (option.longName == long_name) {
            return option;
        }
    }
    throw;
}

ArgParser::Option ArgParser::getPosOpt(std::string name)
{
    for (auto pos_option : pos_options) {
        if (pos_option.longName == name) {
            return pos_option;
        }
    }
    throw;
}

void ArgParser::parseLongOpt(std::string arg)
{
    std::size_t pos = arg.find('=');
    if (pos == 2) {
        throw;
    }
    std::string opt_str = arg.substr(2, pos - 2);

    Option opt = getOpt(opt_str);
    if (pos == -1) {
        parsed_options[opt] = "";
    } else {
        parsed_options[opt] = arg.substr(pos + 1);
    }
}

std::vector<std::string> ArgParser::getPosOptArgs(std::string name)
{
    Option opt = getPosOpt(name);
    return parsed_pos_options[opt];
}

bool ArgParser::isEmpty() { return hasNoOptions() && hasNoPosOptions(); }

bool ArgParser::hasNoOptions() { return parsed_options.size() == 0; }

bool ArgParser::hasNoPosOptions() { return parsed_pos_options.size() == 0; }
