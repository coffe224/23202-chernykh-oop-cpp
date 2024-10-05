#include <string>
#include <vector>
#include <list>
#include <map>

class Statistics {
    public:
        Statistics();
        void countWord(std::string& word);
        void countList(std::list<std::string>& list);
        void printMap();
        std::vector<std::tuple<std::string, int, double>> returnStatistics();
    private:
        void SortStatistics(std::vector<std::tuple<std::string, int, double>>& stat_vec);
        static bool CompareTuples(const std::tuple<std::string, int, double>& t1, const std::tuple<std::string, int, double>& t2);
        std::map<std::string, int> wordsMap;
        int wordsTotal;
};