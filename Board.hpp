#pragma once

#include "City.hpp"
#include "Color.hpp"
#include <iostream>
#include <map>
#include <vector> // not needed
#include <set>

namespace pandemic {
    class Board {
    private:
        static std::map<std::string, std::tuple<std::string, std::vector<std::string>>> connections; // map which gives us by value city:
        static std::map<City, std::string> toStringCity;                                             // (1)Color,
        std::map<City, int> diseases;                                                                // (2)vector with connected cities
        std::set<City> researchStation;                                                              // todo Try to make City instead of string
        std::set<City> cures;

    public:
        Board();
        friend std::ostream &operator<<(std::ostream &os, const Board &b);
        int &operator[](City);
        bool is_clean();
        void remove_cures();
        bool isResearchStation(City);
        bool isCured(City);
        int getDiseaseCubes(City);
        std::tuple<Color, std::vector<std::string>> getColorAndConnections(City);
    };
}