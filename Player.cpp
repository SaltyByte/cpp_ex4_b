#include "Player.hpp"

#include <iostream>

using namespace pandemic;
using namespace std;


Player::Player(Board &gameBoard, City city) {

}

Player& Player::treat(City city) {
    Board b;
    return *this;
}

Player& Player::drive(City city) {
    Board b;
    return *this;
}

Player& Player::fly_direct(City city) {
    Board b;
    return *this;
}

Player& Player::fly_charter(City city) {
    Board b;
    return *this;
}

Player& Player::fly_shuttle(City city) {
    Board b;
    return *this;
}

Player& Player::discover_cure(Color color) {

    return *this;

}

Player& Player::take_card(City city) {
    Board b;
    return *this;
}

Player& Player::build() {
    return *this;

}

string Player::role() {
    return "Player";
}