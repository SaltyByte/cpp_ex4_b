#pragma once
#include "Board.hpp"
#include "Color.hpp"
#include <map>
#include <set>

namespace pandemic {
    class Player {
    private:
        Board gboard;
        City location;
        std::set<City> cards;

    public:
        Player(Board&, City);
        Player& treat(City);
        Player& drive(City);
        Player& fly_direct(City);
        Player& fly_charter(City);
        Player& fly_shuttle(City);
        Player& discover_cure(Color);
        Player& take_card(City);
        Player& build();
        virtual std::string role();

    };
}