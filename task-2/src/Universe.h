#include <array>
#include <string>
#include <vector>

class Universe
{
    private:
        std::string universeName;
        std::size_t widthOfField;
        std::size_t heightOfField;

        std::array<bool, 9> birthValues;
        std::array<bool, 9> survivalValues;

        std::vector<std::pair<std::size_t, std::size_t>> alive_cells;

        std::size_t curIteration;

        class Field
        {
            private:
                std::size_t width;
                std::size_t height;
                std::vector<std::vector<bool>> cells;

            public:
                Field();
                ~Field();

                Field(std::size_t width, std::size_t height);
                void swap(Field field);
                void setSize(std::size_t width, std::size_t height);

                void clear();

                void setCell(std::size_t x, std::size_t y, bool value = true);
                bool getCell(std::size_t x, std::size_t y);
                std::size_t getCellNeighbours(std::size_t x, std::size_t y);

                std::vector<std::vector<bool>> getField();
        };

        Field field;
        Field buffer_field;

    public:
        Universe();
        // ~Universe();

        void setSize(std::size_t width,
                     std::size_t height);

        void nextIteration();

        std::size_t getWidth();
        std::size_t getHeight();
        std::size_t getIteration();

        void setName(std::string universe_name);
        std::string getName();

        void setRules(std::array<bool, 9> birth_vals,
                      std::array<bool, 9> surv_vals);

        std::array<bool, 9> getSurvRules();
        std::array<bool, 9> getBirthRules();
 
        void setAliveCells(std::vector<std::pair<std::size_t, std::size_t>>& active_cells);
        std::vector<std::pair<std::size_t, std::size_t>> getAliveCells();
        std::vector<std::vector<bool>> getCurrentField();
};