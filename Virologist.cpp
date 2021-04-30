#include "Virologist.hpp"
#include <string>
using namespace pandemic;
using namespace std;

Virologist::Virologist(Board &gameBoard, City city) : Player(gameBoard, city) {

}
string Virologist::role() {
    return "Virologist";
}
