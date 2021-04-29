#include "Player.hpp"


#include <ostream>
using namespace pandemic;
using namespace std;


Player::Player(Board &gameBoard, City city, int numberOfCards) {

}

Player Player::treat(City city) {
    Board b;
    return Player {b, City::Atlanta, 0};
}

Player Player::drive(City city) {
    Board b;
    return Player {b, City::Atlanta, 0};
}

Player Player::fly_direct(City city) {
    Board b;
    return Player {b, City::Atlanta, 0};
}

Player Player::fly_charter(City city) {
    Board b;
    return Player {b, City::Atlanta, 0};
}

Player Player::fly_shuttle(City city) {
    Board b;
    return Player {b, City::Atlanta, 0};
}

void Player::discover_cure(Color color) {

}

Player Player::take_card(City city) {
    Board b;
    return Player {b, City::Atlanta, 0};
}

void Player::build() {

}

std::string Player::role() {
    return std::string();
}
