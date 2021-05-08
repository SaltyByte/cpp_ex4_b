#include "Researcher.hpp"

using namespace std;

namespace pandemic {
    Researcher::Researcher(Board &gameBoard, City city) : Player(gameBoard, city, "Researcher") {}

    Researcher &Researcher::discover_cure(Color color) {
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
        return *this;
    }
}