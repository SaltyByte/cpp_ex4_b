#pragma once
#include "Board.hpp"
#include "Color.hpp"
#include <map>
#include <set>

namespace pandemic {
    class Player {
    private:
        Board playingBoard;
        City location;
        std::set<City> cards;
        std::string job;

    public:
        Player(Board&, City, const std::string&);
        virtual Player& treat(City);
        virtual Player& drive(City);
        virtual Player& fly_direct(City);
        virtual Player& fly_charter(City);
        virtual Player& fly_shuttle(City);
        virtual Player& discover_cure(Color);
        virtual Player& take_card(City);
        virtual Player& build();
        std::string role();

    };
}