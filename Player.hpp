#pragma once
#include "Board.hpp"
#include "Color.hpp"

namespace pandemic {
    class Player {


    public:
        Player(Board&, City);
        Player treat(City);
        Player drive(City);
        Player fly_direct(City);
        Player fly_charter(City);
        Player fly_shuttle(City);
        void discover_cure(Color);
        Player take_card(City);
        void build();
        std::string role();

    };
}