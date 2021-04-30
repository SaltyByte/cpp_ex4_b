#include "Medic.hpp"
#include <string>
using namespace pandemic;
using namespace std;

Medic::Medic(Board &gameBoard, City city) : Player(gameBoard, city) {

}
string Medic::role() {
    return "Medic";
}
