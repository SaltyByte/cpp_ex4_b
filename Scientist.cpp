#include "Scientist.hpp"
#include <string>
using namespace pandemic;
using namespace std;

Scientist::Scientist(Board &gameBoard, City city, int numberOfCards) : Player(gameBoard, city) {

}
string Scientist::role() {
    return "Scientist";
}
