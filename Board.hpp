#pragma once

#include "City.hpp"
#include <iostream>
#include <map>
#include <string>

namespace pandemic {
    class Board {
    private:
        std::map<City, int> board;
        void deleteCities();

    public:
        Board();
        int& operator[](City);
        friend std::ostream &operator<<(std::ostream &os, const Board& b);
        bool is_clean();
    };
}
