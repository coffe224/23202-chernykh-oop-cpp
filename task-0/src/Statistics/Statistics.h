#include <list>
#include <map>
#include <string>
#include <vector>

class Statistics
{
    public:
        Statistics();
        void put(const std::string& word);
        void put(const std::list<std::string>& list);
        std::vector<std::tuple<std::string, int, double>> getStats();

    private:
        void sortStats(
            std::vector<std::tuple<std::string, int, double>>& stat_vec);
        static bool
        compareTuples(const std::tuple<std::string, int, double>& t1,
                      const std::tuple<std::string, int, double>& t2);

        std::map<std::string, int> wordsMap;
        int wordsTotal;
};