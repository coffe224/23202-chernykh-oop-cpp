#include <list>
#include <string>

class Parser
{
    public:
        std::list<std::string> getWords(std::string& line);

    private:
        std::string::iterator wordStartIt;
        std::string::iterator wordEndIt;
        std::string::iterator lineEndIt;

        bool isDelim(char l);
        void lowerWord(std::string& word);
        void findWordStart();
        void findWordEnd();
};