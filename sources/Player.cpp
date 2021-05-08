#include "Player.hpp"
#include <stdexcept>


using namespace std;

namespace pandemic {

    Player::Player(Board &gameBoard, City city, const string &job) {
        this->job = job;
        this->location = city;
        this->playingBoard = &gameBoard;
    }

    Player &Player::treat(City city) {
        if (this->playingBoard->operator[](city) < 1) {
            throw invalid_argument("Cant treat with no disease");
        }

        Color cityColor = Board::getColor(city);
        if (location == city) {
            if (this->playingBoard->isCured(cityColor)) {
                this->playingBoard->operator[](city) = 0;
            }
            else {
                this->playingBoard->operator[](city)--;
            }
        }
        return *this;
    }

    Player &Player::drive(City city) {
        set<City> cities = Board::getNeighbors(this->location);
        if (cities.find(city) == cities.end()) {
            throw invalid_argument("Cant drive to not connected city");
        }
        this->location = city;
        return *this;
    }

    Player &Player::fly_direct(City city) {
        if (cards.find(city) == cards.end() || this->location == city) {
            throw invalid_argument("Cant fly_direct without location city card or to same city");
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
        if (this->playingBoard->isResearchStation(city) && this->playingBoard->isResearchStation(this->location) && city != this->location) {
            this->location = city;
            return *this;
        }
        throw invalid_argument(
                "Cant fly_shuttle to city with no research station or from city with no research station");
    }

    Player &Player::discover_cure(Color color) {
        if (!playingBoard->isResearchStation(this->location)) {
            throw invalid_argument("Cant cure with no research station");
        }
        if (playingBoard->isCured(color)) {
            return *this;
        }
        const int cardsToThrow = 5;
        int colorCount = 0;
        set<City> whichCard;
        for (const auto &card : this->cards) {
            Color cityColor = Board::getColor(card);
            if (cityColor == color) {
                colorCount++;
                whichCard.insert(card);
            }
        }
        if (colorCount < cardsToThrow) {
            throw invalid_argument("Cant cure with less than 5 cards of same color");
        }
        for (const auto &card : whichCard) {
                this->cards.erase(card);
        }
        this->playingBoard->setCure(color);
        //this->playingBoard->updateCuredCities(color);
        return *this;
    }

    Player &Player::take_card(City city) {
        this->cards.insert(city);
        return *this;
    }

    Player &Player::build() {
        if (this->playingBoard->isResearchStation(this->location)) {
            return *this;
        }
        if (this->cards.find(this->location) == this->cards.end()) {
            throw invalid_argument("No correct city card in hand");
        }
        this->playingBoard->setResearchStation(this->location);
        this->cards.erase(this->location);
        return *this;
    }

    string Player::role() {
        return this->job;
    }

    void Player::remove_cards() {
        cards.clear();
    }
}