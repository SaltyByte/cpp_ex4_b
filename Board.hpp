#pragma once

#include "City.hpp"
#include "Color.hpp"
#include <iostream>
#include <map>
#include <set>

namespace pandemic {
    class Board {
    private:
        static std::map<City, std::tuple<Color, std::set<City>>> connections; // map which gives us by value city:
        static std::map<City, std::string> cityToString;                                             // (1)Color,
        std::map<City, int> diseases;                                                                // (2)vector with connected cities
        std::set<City> researchStation;
        std::set<Color> cures;
        static void initBoard();
        static std::string getColor(Color);

    public:
        Board();
        friend std::ostream &operator<<(std::ostream &os, const Board &b);
        int &operator[](City);
        bool is_clean();
        void remove_cures();
        bool isResearchStation(City);
        void setResearchStation(City);
        bool isCured(Color);
        std::tuple<Color, std::set<City>> getColorAndConnections(City);
    };
}