#pragma once
#include "Player.hpp"

namespace pandemic {
    class Scientist : public Player{
    private:
        int cardsNeededToCure;

    public:
        Scientist(Board&, City, int);
        Scientist& discover_cure(Color) override;
    };
}
