#pragma once

#include "City.hpp"
#include "Color.hpp"
#include <iostream>
#include <map>
#include <set>

namespace pandemic {
    class Board {
    private:
        static std::map<City, std::tuple<Color, std::set<City>, std::string>> connections; // map which gives us by value city:
        std::map<City, int> diseases;                                                      // (1)Color,
        std::set<City> researchStation;                                                    // (2)vector with connected cities
        std::set<Color> cures;
        static void initBoard();
        static std::string getColorString(Color);
        static std::string getCityString(City);

    public:
        Board();
        friend std::ostream &operator<<(std::ostream &os, const Board &b);
        int &operator[](City);
        bool is_clean();
        void remove_stations();
        void remove_cures();
        bool isResearchStation(City);
        void setResearchStation(City);
        void setCure(Color);
        bool isCured(Color);
        static Color getColor(City);
        static std::set<City> getNeighbors(City);
    };
}