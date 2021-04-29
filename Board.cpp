#include "Board.hpp"
#include <map>
#include <string>

using namespace pandemic;
using namespace std;

map<string, City> board;

int& Board::operator[](City city) {
    return board[city];
}


unsigned char Board::is_clean() {
    return board.size();
}

ostream &pandemic::operator<<(ostream &os, const Board &b) {
    os << "Hello" << endl;
    return os;
}
