#pragma once
#include "Player.hpp"

namespace pandemic {
    class GeneSplicer : public Player{
    public:
        GeneSplicer(Board&, City);
        //std::string role() override;

    };
}