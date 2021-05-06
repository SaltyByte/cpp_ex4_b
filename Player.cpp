#include "Player.hpp"
#include "Board.hpp"
#include <iostream>
#include <tuple>
#include <vector>
#include <stdexcept>

using namespace pandemic;
using namespace std;


Player::Player(Board &gameBoard, City city, const string &job) {
    this->job = job;
    this->location = city;
    this->playingBoard = gameBoard;
}

Player &Player::treat(City city) {
    if (playingBoard[city] < 1) {
        throw invalid_argument("Cant treat with no disease");
    }

    if (location == city) {
        this->playingBoard[city]--;
    }
    return *this;
}

Player &Player::drive(City city) {
    if (get<1>(playingBoard.getColorAndConnections(this->location)).find(city) ==
        get<1>(playingBoard.getColorAndConnections(this->location)).end()) {
        throw invalid_argument("Cant drive to not connected city");
    }
    this->location = city;
    return *this;
}

Player &Player::fly_direct(City city) {
    if (cards.find(city) == cards.end()) {
        throw invalid_argument("Cant fly_direct without location city card");
    }
    this->cards.erase(city);
    this->location = city;
    return *this;

}

Player &Player::fly_charter(City city) {
    if (this->cards.find(this->location) == this->cards.end()) {
        throw invalid_argument("Cant fly_charter without location city card");
    }
    this->cards.erase(this->location);
    this->location = city;
    return *this;
}

Player &Player::fly_shuttle(City city) {
    if (this->playingBoard.isResearchStation(city) && this->playingBoard.isResearchStation(this->location)) {
        this->location = city;
        return *this;
    }
    throw invalid_argument("Cant fly_shuttle to city with no research station or from city with no research station");
}

Player &Player::discover_cure(Color color) {
    if (!playingBoard.isResearchStation(this->location)) {
        throw invalid_argument("Cant cure with no research station");
    }
    if (playingBoard.isCured(color)) {
        throw invalid_argument("Cant cure, already cured");
    }
    int colorCount = 0;
    set<City> whichCard;
    for (auto &card : this->cards) {
        Color cityColor = get<0>(this->playingBoard.getColorAndConnections(card));
        if (cityColor == color) {
            colorCount++;
            whichCard.insert(card);
        }
    }
    if (colorCount < 5) {
        throw invalid_argument("Cant cure with less than 5 cards of same color");
    }
    int i = 0;
    for (auto &card : whichCard) {
        if (i < 5) {
            this->cards.erase(card);
            i++;
        } else {
            break;
        }
    }
    return *this;
}

Player &Player::take_card(City city) {
    this->cards.insert(city);
    return *this;
}

Player &Player::build() {
    if (this->playingBoard.isResearchStation(this->location)) {
        return *this;
    }
    this->playingBoard.setResearchStation(this->location);
    return *this;
}

string Player::role() {
    return this->job;
}