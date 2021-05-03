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
        getline(file, mainCity, ' '); // get main city
        getline(file, color, ' '); // get color
        getline(file, cities, '\r'); // get connected cities
        mainCity.erase(remove(mainCity.begin(), mainCity.end(), '\n'), mainCity.end()); // erase \n
        vector<string> vec; // vector to store connected cities
        istringstream stringStream(cities);
        while (!stringStream.eof()) {
            getline(stringStream, city, ' ');
            vec.insert(vec.begin(), city);
        }
        connections[mainCity] = make_tuple(color, vec);
        toStringCity[(City) enumIndex] = mainCity;
        enumIndex++;
    }
    for (auto &val : toStringCity) {
        diseases[val.first] = 0;
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

int &Board::operator[](City city) {
    return diseases[city];
}

ostream& pandemic::operator<<(ostream &os, const Board &b) {
    os << "Number of research centers: " << b.researchStation.size() << endl;
    for (const auto &val : b.researchStation) {
        os << "Research centers at cities: " << b.toStringCity.at(val) << endl; // fix this, city is not showing good
    }
    os << "Number of cures discovers: " << b.cures.size() << endl;
    for (const auto &val : b.cures) {
        os << "cures discovered at: " << b.toStringCity.at(val) << endl; // fix this, city is not showing good
    }
    os << "Number of Cities infected: " << b.diseases.size() << endl;
    for (const auto &val : b.diseases) {
        os << "City: " << b.toStringCity.at(val.first) << endl << "Number of diseases: " << val.second << endl;
    }
    return os;
}


bool Board::is_clean() {
    for (auto &val : diseases) { // if(all_of(diseases.begin(), diseases.end(), [](auto val){return val.second > 0;}))
        if (val.second > 0) {
            return false;
        }
    }
    return true;
}

void Board::remove_cures() {
    for (auto &val : cures) {
        cures.erase(val);
    }
}