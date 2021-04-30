#include "Researcher.hpp"
#include <string>
using namespace pandemic;
using namespace std;

Researcher::Researcher(Board &gameBoard, City city) : Player(gameBoard, city) {

}

string Researcher::role() {
    return "Researcher";
}