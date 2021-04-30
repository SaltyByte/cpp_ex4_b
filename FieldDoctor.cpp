#include "FieldDoctor.hpp"
#include <string>
using namespace pandemic;
using namespace std;

FieldDoctor::FieldDoctor(Board &gameBoard, City city) : Player(gameBoard, city) {

}
string FieldDoctor::role() {
    return "FieldDoctor";
}
