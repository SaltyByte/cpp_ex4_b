#include "OperationsExpert.hpp"
#include <string>

using namespace std;
namespace pandemic {
    OperationsExpert::OperationsExpert(Board &gameBoard, City city) : Player(gameBoard, city, "OperationsExpert") {}

    OperationsExpert &OperationsExpert::build() {
        if (this->playingBoard->isResearchStation(this->location)) {
            return *this;
        }
        this->playingBoard->setResearchStation(this->location);
        return *this;
    }
}