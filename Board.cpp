#include "Board.hpp"
#include "Color.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>


using namespace pandemic;
using namespace std;


Board::Board() {

    ifstream file("cities_map.txt");
    string mainCity;
    string color;
    string cities;
    string city;
    int enumIndex = 0;
    while (!file.eof()) {
        getline(file, mainCity, ' ');
        getline(file, color, ' ');
        getline(file, cities, '\r');
        mainCity.erase(remove(mainCity.begin(),mainCity.end(),'\n'),mainCity.end());

        vector<string> vec;
        istringstream stringStream(cities);
        while (!stringStream.eof()) {
            getline(stringStream, city, ' ');
            vec.insert(vec.begin(), city);
        }
        connections[mainCity] = make_tuple(color,vec);
        toStringCity[(City)enumIndex] = mainCity;
        enumIndex++;
    }
}
string getColor(Color color) {
    switch (color) {
        case Color::Yellow:
            return "Yellow";
        case Color::Black:
            return "Black";
        case Color::Blue:
            return "Blue";
        case Color::Red:
            return "Red";
    }
}


int& Board::operator[](City city) {
    return diseases[city];
}

ostream& pandemic::operator<<(ostream &os, const Board &b) {
    os << "Number of research centers: " << b.researchStation.size() << endl;
    for (const auto &val : b.researchStation) {
        os << "Research centers at cities: " << b.toStringCity.at(val) << endl; // fix this, city is not showing good
    }
    os << "Number of cures discovers: " << b.cures.size() << endl;
    for (const auto &val : b.cures) {
        os << "\ncures discovered at: " << b.toStringCity.at(val) << endl; // fix this, city is not showing good
    } os << "Number of Cities infected: " << b.diseases.size() << endl;
    for (const auto &val : b.diseases) {
        os << "City: " << b.toStringCity.at(val.first) << endl <<  "Number of diseases: " << val.second << endl;


    }
    return os;
}


bool Board::is_clean() {
    return diseases.empty();
}

void Board::remove_cures() {
    for (auto val : cures) {
        cures.erase(val);
    }
}
