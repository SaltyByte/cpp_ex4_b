#pragma once

#include "City.hpp"
#include "Color.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>

namespace pandemic {
    class Board {
    private:
        std::map<std::string, std::tuple<std::string,std::vector<std::string>>> connections; // map which gives us by value city:
        std::map<City, int> diseases;                                    // (1)Color,
        std::set<City> researchStation;                                  // (2)the 4 cities which its connected to,
        std::set<City> cures;
        std::map<City, std::string> toStringCity;


    public:
        Board();
        int& operator[](City);
        friend std::ostream &operator<<(std::ostream &os, const Board& b);
        bool is_clean();
        void remove_cures();
    };
}
