#include "Medic.hpp"
using namespace std;

namespace pandemic {
    Medic::Medic(Board &gameBoard, City city) : Player(gameBoard, city,"Medic") {}

    Medic &Medic::drive(City city) {
        set<City> cities = Board::getNeighbors(this->location);
        if (cities.find(city) == cities.end()) {
            throw invalid_argument("Cant drive to not connected city");
        }
        this->location = city;
        Color cityColor = Board::getColor(city);
        if (this->playingBoard->isCured(cityColor)) {
            this->playingBoard->operator[](city) = 0;
        }
        return *this;
    }

    Medic &Medic::fly_direct(City city) {
        if (cards.find(city) == cards.end() || this->location == city) {
            throw invalid_argument("Cant fly_direct without location city card or to same city");
        }
        this->cards.erase(city);
        this->location = city;
        Color cityColor = Board::getColor(city);
        if (this->playingBoard->isCured(cityColor)) {
            this->playingBoard->operator[](city) = 0;
        }
        return *this;
    }

    Medic &Medic::fly_charter(City city) {
        if (this->cards.find(this->location) == this->cards.end()) {
            throw invalid_argument("Cant fly_charter without location city card");
        }
        this->cards.erase(this->location);
        this->location = city;
        Color cityColor = Board::getColor(city);
        if (this->playingBoard->isCured(cityColor)) {
            this->playingBoard->operator[](city) = 0;
        }
        return *this;
    }

    Medic &Medic::fly_shuttle(City city) {
        if (this->playingBoard->isResearchStation(city) && this->playingBoard->isResearchStation(this->location) && city != this->location) {
            this->location = city;
            Color cityColor = Board::getColor(city);
            if (this->playingBoard->isCured(cityColor)) {
                this->playingBoard->operator[](city) = 0;
            }
            return *this;
        }
        throw invalid_argument(
                "Cant fly_shuttle to city with no research station or from city with no research station or to same ciy");
    }

    Medic &Medic::treat(City city) {
        if (this->playingBoard->operator[](city) < 1) {
            throw invalid_argument("Cant treat with no disease");
        }
        if (location == city) {
            this->playingBoard->operator[](city) = 0;
        }
        return *this;
    }
}