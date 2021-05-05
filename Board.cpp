#include "Board.hpp"
#include "Color.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

namespace pandemic {
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
            default:
                return "ERROR";
        }
    }

    int &Board::operator[](City city) {
        return diseases[city];
    }

    ostream &operator<<(ostream &os, const Board &b) {
        os << "Research centers built: " << b.researchStation.size() << endl;
        for (const auto &val : b.researchStation) {
            os << "Research centers at cities: " << b.toStringCity.at(val) << endl;
        }
        os << "Cures discovers: " << b.cures.size() << endl;
        for (const auto &val : b.cures) {
            os << "cures discovered at: " << b.toStringCity.at(val) << endl;
        }
        int infected = 0;
        for (const auto &val : b.diseases) {
            if (val.second > 0) {
                infected++;
                os << "City: " << b.toStringCity.at(val.first) << ", Number of diseases: " << val.second << endl;
            }
        }
        os << "Number of Cities infected: " << infected << endl;
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
        for (const auto &val : cures) {
            cures.erase(val);
        }
    }

    bool Board::isResearchStation(City city) {
        if (researchStation.find(city) != researchStation.end()) {
            return true;
        }
        return false;
    }

    bool Board::isCured(City city) {
        if (cures.find(city) != cures.end()) {
            return true;
        }
        return false;
    }

    int Board::getDiseaseCubes(City city) {
        return diseases[city];
    }
}