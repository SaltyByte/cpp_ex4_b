#pragma once
#include "Player.hpp"

namespace pandemic {
    class Virologist : public Player{
    public:
        Virologist(Board&, City);
        //std::string role() override;

    };
}