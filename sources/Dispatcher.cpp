#include "Dispatcher.hpp"
#include <string>

using namespace std;

namespace pandemic {
    Dispatcher::Dispatcher(Board &gameBoard, City city) : Player(gameBoard, city, "Dispatcher") {}

    Dispatcher &Dispatcher::fly_direct(City city) {
        if (this->playingBoard->isResearchStation(this->location) && this->location != city) {
            this->location = city;
            return *this;
        }
        if (cards.find(city) == cards.end()) {
            throw invalid_argument("Cant fly_direct without location city card or to same city");
        }
        this->cards.erase(city);
        this->location = city;
        return *this;
    }
}

