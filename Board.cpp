#include "Board.hpp"
#include <map>
#include <string>

using namespace pandemic;
using namespace std;

map<City, int> board;

Board::Board() = default ;


int& Board::operator[](City city) {
    return board[city];
}

ostream &pandemic::operator<<(ostream &os, const Board &b) {


    os << "Hello" << endl;
    return os;
}


unsigned char Board::is_clean() {
    for (auto &val : board) {
        if (val.second == 0) {
            board.erase(val.first);
        }
    }
    return board.empty();
}

void Board::remove_cures() {

}



