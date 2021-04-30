#include "Dispatcher.hpp"
#include <string>
using namespace pandemic;
using namespace std;

Dispatcher::Dispatcher(Board &gameBoard, City city) : Player(gameBoard, city) {

}
string Dispatcher::role() {
    return "Dispatcher";
}

