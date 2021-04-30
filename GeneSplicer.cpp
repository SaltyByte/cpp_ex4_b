#include "GeneSplicer.hpp"
#include <string>
using namespace pandemic;
using namespace std;

GeneSplicer::GeneSplicer(Board &gameBoard, City city) : Player(gameBoard, city) {

}
string GeneSplicer::role() {
    return "GeneSplicer";
}
