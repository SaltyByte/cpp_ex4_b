#include "Player.hpp"


#include <ostream>
using namespace pandemic;
using namespace std;


Player::Player(Board &gameBoard, City city) {

}

Player Player::treat(City city) {
    Board b;
    return Player {b, City::Atlanta};
}

Player Player::drive(City city) {
    Board b;
    return Player {b, City::Atlanta};
}

Player Player::fly_direct(City city) {
    Board b;
    return Player {b, City::Atlanta};
}

Player Player::fly_charter(City city) {
    Board b;
    return Player {b, City::Atlanta};
}

Player Player::fly_shuttle(City city) {
    Board b;
    return Player {b, City::Atlanta};
}

void Player::discover_cure(Color color) {

}

Player Player::take_card(City city) {
    Board b;
    return Player {b, City::Atlanta};
}

void Player::build() {

}

string Player::role() {
    return string();
}
