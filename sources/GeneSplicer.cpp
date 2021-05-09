#include "GeneSplicer.hpp"

using namespace std;
namespace pandemic {
    GeneSplicer::GeneSplicer(Board &gameBoard, City city) : Player(gameBoard, city, "GeneSplicer") {}

    GeneSplicer &GeneSplicer::discover_cure(Color color) {
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
            colorCount++;
            whichCard.insert(card);
        }
        if (colorCount < cardsToThrow) {
            throw invalid_argument("Cant cure with less than 5 cards of same color");
        }
        for (const auto &card : whichCard) {
            this->cards.erase(card);
        }
        this->playingBoard->setCure(color);
        return *this;
    }
}