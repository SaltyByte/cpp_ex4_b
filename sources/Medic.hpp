#pragma once
#include "Player.hpp"

namespace pandemic {
    class Medic : public Player{
    public:
        Medic(Board&, City);
        Medic& drive(City) override;
        Medic& fly_direct(City) override;
        Medic& fly_charter(City) override;
        Medic& fly_shuttle(City) override;
        Medic& treat(City) override;

    };
}