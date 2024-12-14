#include <iostream>
#include <string>
#include <map>
#include <vector>

class ArgParser
{
    private:
        class Option
        {
            public:
                char shortName;
                std::string longName;
                bool positional;
                bool hasArgs;
                int numOfArgs;

                bool operator<(Option const & rhs) const {
                    return this->longName < rhs.longName;
                }

                bool operator==(Option const & rhs) const {
                    return this->longName == rhs.longName;
                }
                // переставить в private?
        };
        std::vector<Option> pos_options;
        std::vector<Option> options;
        std::map<Option, std::string> parsed_options;
        std::map<Option, std::vector<std::string>> parsed_pos_options;

        Option getOpt(char short_name);
        Option getOpt(std::string long_name);
        Option getPosOpt(std::string name);
        void parseLongOpt(std::string arg);

    public:
        ArgParser();

        void addPosOption(std::string name, int num_of_args);
        void addOption(char short_name, std::string long_name, bool has_args);
        void parseArguments(int argc, char const *argv[]);

        template <typename T> bool hasOpt(T name)
        {
            Option opt = getOpt(name);
            bool is_in_opts = parsed_options.find(opt) != parsed_options.end();
            bool is_in_pos_opts =
                parsed_pos_options.find(opt) != parsed_pos_options.end();
            return is_in_opts || is_in_pos_opts;
        }

        template <typename T> std::string getOptArgs(T name)
        {
            Option opt = getOpt(name);
            if (hasOpt(name)) {
                return parsed_options[opt];
            } else {
                return "";
            }
        }

        bool hasPosOpt(std::string name);
        std::vector<std::string> getPosOptArgs(std::string name);

        bool isEmpty();
        bool hasNoOptions();
        bool hasNoPosOptions();
};