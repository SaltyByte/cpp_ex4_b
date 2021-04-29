#include "Board.hpp"
#include <map>
#include <string>

using namespace pandemic;
using namespace std;

map<City, int> board;

Board::Board() {}


int& Board::operator[](City city) {
    for (auto& val : board) {
        if (val.second == 0) {
            board.erase(val.first);
        }
    }

    if (board.find(city) == board.end()) {
        return board[city];
    }
}


unsigned char Board::is_clean() {
    return board.empty();
}

ostream &pandemic::operator<<(ostream &os, const Board &b) {
    os << "Hello" << endl;
    return os;
}


