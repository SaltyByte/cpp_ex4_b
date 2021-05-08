#include "Virologist.hpp"
using namespace std;

namespace pandemic {
    Virologist::Virologist(Board &gameBoard, City city) : Player(gameBoard, city, "Virologist") {}

    Virologist &Virologist::treat(City city) {
        if (this->playingBoard->operator[](city) < 1) {
            throw invalid_argument("Cant treat with no disease");
        }
        Color cityColor = Board::getColor(city);
        if (this->location == city) {
            if (this->playingBoard->isCured(cityColor)) {
                this->playingBoard->operator[](city) = 0;
            }
            else {
                this->playingBoard->operator[](city)--;
            }
            return *this;
        }
        if (this->cards.find(city) == this->cards.end()){
            throw invalid_argument("Cant treat with no card");
        }
        if (this->playingBoard->isCured(cityColor)) {
            this->playingBoard->operator[](city) = 0;
        }
        else {
            this->playingBoard->operator[](city)--;
        }
        this->cards.erase(city);
        return *this;
    }
}