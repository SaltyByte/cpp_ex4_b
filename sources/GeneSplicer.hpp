#pragma once
#include "Player.hpp"

namespace pandemic {
    class GeneSplicer : public Player{
    public:
        GeneSplicer(Board&, City);
        GeneSplicer &discover_cure(Color) override;
    };
}