#pragma once

#include "City.hpp"
#include <ostream>
#include <map>
#include <string>

namespace pandemic {
    class Board {
    private:
        std::map<City, int> board;


    public:

        friend std::ostream &operator<<(std::ostream&, const Board&);
        int& operator[](City);
        unsigned char is_clean();
    };
}
