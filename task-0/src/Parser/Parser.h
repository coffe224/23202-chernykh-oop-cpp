#include <string>
#include <list>

class Parser {
    public:
        void parseLine(std::string& line, std::list<std::string>& parsed_list);

    private:
        std::string::iterator wordStartIt;
        std::string::iterator wordEndIt;
        std::string::iterator lineEndIt;

        bool isDelim(char l);
        void findWordStart();
        void findWordEnd();
};