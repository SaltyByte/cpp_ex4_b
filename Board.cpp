#include "Board.hpp"
#include <map>
#include <string>
#include <iostream>


using namespace pandemic;
using namespace std;


Board::Board() = default ;

void Board::deleteCities() {
    for (const auto &val : board) {
        if (val.second == 0) {
            board.erase(val.first);
        }
    }
}

int& Board::operator[](City city) {
    return board[city];
    deleteCities();
}

ostream& pandemic::operator<<(ostream &os, const Board &b) {
    os << "Number of Cities: " << b.board.size() << endl;
    for (const auto &val : b.board) {
        os << "City: " << int(val.first) << endl <<  "Number of diseases: " << val.second << endl; // add just the city and this is finished
    }
    return os;
}


bool Board::is_clean() {
    deleteCities();
    return board.empty();
}