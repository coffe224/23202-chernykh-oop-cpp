#include <array>
#include <string>
#include <vector>

class Universe
{
    private:
        std::string universeName;
        int widthOfField;
        int heightOfField;

        std::array<bool, 9> birthValues;
        std::array<bool, 9> survivalValues;

        std::vector<std::pair<int, int>> alive_cells;

        int curIteration;

        class Field
        {
            private:
                int width;
                int height;
                std::vector<std::vector<bool>> cells;

            public:
                Field();
                ~Field();

                Field(int width, int height);
                void swap(Field field);
                void setSize(int width, int height);

                void clear();

                void setCell(int x, int y, bool value = true);
                bool getCell(int x, int y);
                int getCellNeighbours(int x, int y);

                std::vector<std::vector<bool>> getField();
        };

        Field field;
        Field buffer_field;

    public:
        Universe();
        // ~Universe();

        void setSize(int width,
                     int height);

        void nextIteration();

        int getWidth();
        int getHeight();

        void setName(std::string universe_name);
        std::string getName();

        void setRules(std::array<bool, 9> birth_vals,
                      std::array<bool, 9> surv_vals);

        std::array<bool, 9> getSurvRules();
        std::array<bool, 9> getBirthRules();

        int getIteration();
        void setAliveCells(std::vector<std::pair<int, int>>& active_cells);
        std::vector<std::pair<int, int>> getAliveCells();
        std::vector<std::vector<bool>> getCurrentField();
};