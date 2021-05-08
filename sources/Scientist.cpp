#include "Scientist.hpp"
#include <string>
using namespace std;

namespace pandemic {
    Scientist::Scientist(Board &gameBoard, City city, int numberOfCards) : Player(gameBoard, city, "Scientist") {
        this->cardsNeededToCure = numberOfCards;
    }

    Scientist &Scientist::discover_cure(Color color) {
        if (!playingBoard->isResearchStation(this->location)) {
            throw invalid_argument("Cant cure with no research station");
        }
        if (playingBoard->isCured(color)) {
            return *this;
        }
        const int cardsToThrow = this->cardsNeededToCure;
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
            throw invalid_argument("Cant cure with less than needed cards of same color");
        }
        for (const auto &card : whichCard) {
            this->cards.erase(card);
        }
        this->playingBoard->setCure(color);
        return *this;
    }
}
