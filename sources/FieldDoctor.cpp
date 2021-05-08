#include "FieldDoctor.hpp"
using namespace std;

namespace pandemic {
    FieldDoctor::FieldDoctor(Board &gameBoard, City city) : Player(gameBoard, city, "FieldDoctor") {}

    FieldDoctor &FieldDoctor::treat(City city) {
        if (this->playingBoard->operator[](city) < 1) {
            throw invalid_argument("Cant treat with no disease");
        }
        set<City> neighbors = Board::getNeighbors(this->location);
        Color cityColor = Board::getColor(city);
        if (location == city || neighbors.find(city) != neighbors.end()) {
            if (this->playingBoard->isCured(cityColor)) {
                this->playingBoard->operator[](city) = 0;
            }
            else {
                this->playingBoard->operator[](city)--;
            }
            return *this;
        }
        throw invalid_argument("Cant treat, too far away");
    }

}
