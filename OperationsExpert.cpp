#include "OperationsExpert.hpp"
#include <string>

using namespace pandemic;
using namespace std;

OperationsExpert::OperationsExpert(Board &gameBoard, City city) : Player(gameBoard, city) {

}
string OperationsExpert::role() {
    return "OperationsExpert";
}

