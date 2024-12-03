#include <iostream>
#include <string>
#include <map>
#include <vector>

// ./game
// ./game [input_file]
// ./game [input_file] [-i N] [-o output_file]
// ./game [input_file] [--iterations=N] [--output=output_file]

// 1st [] - input file (without option argument) - try to get option without
// argument 2nd [] - iterations (with -i or --iterations) - try to get option
// with argument (-i and --iterations=) 3rd [] - output file (with -o or
// --output) - try to get option with argument (-o and --output=)

// argc > 2: gets -> mode 3: input_filename, number_of_iterations,
// output_filename

// empty
// argc == 1: gets -> mode 2

// 1st [] - input file only.
// argc == 2: gets -> mode 1: input_filename

// passInput()

// std::string getOption("-i", "--iterations")
// std::string getOption("-o", "--output")

// getOption("i", "iterations")
// getArgument()

// class ArgParser
// {
//     private:
//         std::vector<std::string> words;
//     public:
//         void passInput(int argc, char const *argv[]);
//         std::string getOption(std::string short_option, std::string
//         full_option); std::string getArgument();
// };

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
        std::map<std::string, std::vector<std::string>> getOptions();

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

        std::vector<std::string> getPosOptArgs(std::string name);

        bool isEmpty();
        bool hasNoOptions();
        bool hasNoPosOptions();
};