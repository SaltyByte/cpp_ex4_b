#include "Board.hpp"
#include "Color.hpp"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

namespace pandemic {
    map<City, tuple<Color, set<City>>> Board::connections; // static because we need to read only 1 times.
    map<City, string> Board::cityToString;

    Board::Board() {
        if (connections.empty()) {
            initBoard();
        }
        for (auto &val : cityToString) {
            diseases[val.first] = 0;
        }
    }

    int &Board::operator[](City city) {
        return diseases[city];
    }


    ostream &operator<<(ostream &os, const Board &b) {
        os << "Research centers built: " << b.researchStation.size() << endl;
        for (const auto &val : b.researchStation) {
            os << "Research centers at cities: " << Board::cityToString.at(val) << endl;
        }
        os << "Cures discovers: " << b.cures.size() << endl;
        for (const auto &color : b.cures) {
            os << "cures discovered at: " << Board::getColor(color) << endl;
        }
        int infected = 0;
        for (const auto &val : b.diseases) {
            if (val.second > 0) {
                infected++;
                os << "City: " << Board::cityToString.at(val.first) << ", Number of diseases: " << val.second << endl;
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

    void Board::setResearchStation(City city) {
        if (!isResearchStation(city)){
            researchStation.insert(city);
        }
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
    bool Board::isCured(Color color) {
        if (cures.find(color) != cures.end()) {
            return true;
        }
        return false;
    }
    tuple<Color, set<City>> Board::getColorAndConnections(City city) {
        return connections[city];
    }
    std::string Board::getColor(Color color) {
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
                return "Error";
        }
    }

    void Board::initBoard() {
        connections[City::Algiers] = make_tuple(Color::Black, set<City>{City::Madrid, City::Paris, City::Istanbul, City::Cairo});
        connections[City::Atlanta] = make_tuple(Color::Blue, set<City>{City::Chicago, City::Miami, City::Washington});
        connections[City::Baghdad] = make_tuple(Color::Black, set<City>{City::Tehran, City::Istanbul, City::Cairo, City::Riyadh, City::Karachi});
        connections[City::Bangkok] = make_tuple(Color::Red, set<City>{City::Kolkata, City::Chennai, City::Jakarta, City::HoChiMinhCity, City::HongKong});
        connections[City::Beijing] = make_tuple(Color::Red, set<City>{City::Shanghai, City::Seoul});
        connections[City::Bogota] = make_tuple(Color::Yellow, set<City>{City::MexicoCity, City::Lima, City::Miami, City::SaoPaulo, City::BuenosAires});
        connections[City::BuenosAires] = make_tuple(Color::Yellow, set<City>{City::Bogota, City::SaoPaulo});
        connections[City::Cairo] = make_tuple(Color::Black, set<City>{City::Algiers, City::Istanbul, City::Baghdad, City::Khartoum, City::Riyadh});
        connections[City::Chennai] = make_tuple(Color::Black, set<City>{City::Mumbai, City::Delhi, City::Kolkata, City::Bangkok, City::Jakarta});
        connections[City::Chicago] = make_tuple(Color::Blue, set<City>{City::SanFrancisco, City::LosAngeles, City::MexicoCity, City::Atlanta, City::Montreal});

        connections[City::Delhi] = make_tuple(Color::Black, set<City>{City::Tehran, City::Karachi, City::Mumbai, City::Chennai, City::Kolkata});
        connections[City::Essen] = make_tuple(Color::Blue, set<City>{City::London, City::Paris, City::Milan, City::StPetersburg});
        connections[City::HoChiMinhCity] = make_tuple(Color::Red, set<City>{City::Jakarta, City::Bangkok, City::HongKong, City::Manila});
        connections[City::HongKong] = make_tuple(Color::Red, set<City>{City::Bangkok, City::Kolkata, City::HoChiMinhCity, City::Shanghai, City::Manila, City::Taipei});
        connections[City::Istanbul] = make_tuple(Color::Black, set<City>{City::Milan, City::Algiers, City::StPetersburg, City::Cairo, City::Baghdad, City::Moscow});
        connections[City::Jakarta] = make_tuple(Color::Red, set<City>{City::Chennai, City::Bangkok, City::HoChiMinhCity, City::Sydney});
        connections[City::Johannesburg] = make_tuple(Color::Yellow, set<City>{City::Kinshasa, City::Khartoum});
        connections[City::Karachi] = make_tuple(Color::Black, set<City>{City::Tehran, City::Baghdad, City::Riyadh, City::Mumbai, City::Delhi});
        connections[City::Khartoum] = make_tuple(Color::Yellow, set<City>{City::Cairo, City::Lagos, City::Kinshasa, City::Johannesburg});
        connections[City::Kinshasa] = make_tuple(Color::Yellow, set<City>{City::Lagos, City::Khartoum, City::Johannesburg,});

        connections[City::Kolkata] = make_tuple(Color::Black, set<City>{City::Delhi, City::Chennai, City::Bangkok, City::HongKong});
        connections[City::Lagos] = make_tuple(Color::Yellow, set<City>{City::SaoPaulo, City::Khartoum, City::Kinshasa,});
        connections[City::Lima] = make_tuple(Color::Yellow, set<City>{City::MexicoCity, City::Bogota, City::Santiago,});
        connections[City::London] = make_tuple(Color::Blue, set<City>{City::NewYork, City::Madrid, City::Essen, City::Paris});
        connections[City::LosAngeles] = make_tuple(Color::Yellow, set<City>{City::SanFrancisco, City::Chicago, City::MexicoCity, City::Sydney});
        connections[City::Madrid] = make_tuple(Color::Blue, set<City>{City::London, City::NewYork, City::Paris, City::SaoPaulo, City::Algiers});
        connections[City::Manila] = make_tuple(Color::Red, set<City>{City::Taipei, City::SanFrancisco, City::HoChiMinhCity, City::Sydney});
        connections[City::MexicoCity] = make_tuple(Color::Yellow, set<City>{City::LosAngeles, City::Chicago, City::Miami, City::Lima, City::Bogota});
        connections[City::Miami] = make_tuple(Color::Yellow, set<City>{City::Atlanta, City::MexicoCity, City::Washington, City::Bogota});
        connections[City::Milan] = make_tuple(Color::Blue, set<City>{City::Essen, City::Paris, City::Istanbul});

        connections[City::Montreal] = make_tuple(Color::Blue, set<City>{City::Chicago, City::Washington, City::NewYork});
        connections[City::Moscow] = make_tuple(Color::Black, set<City>{City::StPetersburg, City::Istanbul, City::Tehran});
        connections[City::Mumbai] = make_tuple(Color::Black, set<City>{City::Karachi, City::Delhi, City::Chennai});
        connections[City::NewYork] = make_tuple(Color::Blue, set<City>{City::Montreal, City::Washington, City::London ,City::Madrid});
        connections[City::Osaka] = make_tuple(Color::Red, set<City>{City::Taipei, City::Tokyo});
        connections[City::Paris] = make_tuple(Color::Blue, set<City>{City::Algiers, City::Essen, City::Madrid, City::Milan, City::London});
        connections[City::Riyadh] = make_tuple(Color::Black, set<City>{City::Baghdad, City::Cairo, City::Karachi});
        connections[City::SanFrancisco] = make_tuple(Color::Blue, set<City>{City::LosAngeles, City::Chicago, City::Tokyo, City::Manila});
        connections[City::Santiago] = make_tuple(Color::Yellow, set<City>{City::Lima});
        connections[City::SaoPaulo] = make_tuple(Color::Yellow, set<City>{City::Bogota, City::BuenosAires, City::Lagos, City::Madrid});

        connections[City::Seoul] = make_tuple(Color::Red, set<City>{City::Beijing, City::Shanghai, City::Tokyo});
        connections[City::Shanghai] = make_tuple(Color::Red, set<City>{City::Beijing, City::HongKong, City::Taipei, City::Seoul, City::Tokyo});
        connections[City::StPetersburg] = make_tuple(Color::Blue, set<City>{City::Essen, City::Istanbul, City::Moscow});
        connections[City::Sydney] = make_tuple(Color::Red, set<City>{City::Jakarta, City::Manila, City::LosAngeles});
        connections[City::Taipei] = make_tuple(Color::Red, set<City>{City::Shanghai, City::HongKong, City::Osaka, City::Manila});
        connections[City::Tehran] = make_tuple(Color::Black, set<City>{City::Baghdad, City::Moscow, City::Karachi, City::Delhi});
        connections[City::Tokyo] = make_tuple(Color::Red, set<City>{City::Seoul, City::Shanghai, City::Osaka, City::SanFrancisco});
        connections[City::Washington] = make_tuple(Color::Blue, set<City>{City::Atlanta, City::NewYork, City::Montreal, City::Miami});
    }
}







//    Board::Board() {
//        if (connections.empty()) {
//            ifstream file("cities_map.txt");
//            string mainCity;
//            string color;
//            string cities;
//            string city;
//            int enumIndex = 0;
//            while (!file.eof()) {
//                getline(file, mainCity, ' '); // get main city
//                getline(file, color, ' '); // get color
//                getline(file, cities, '\r'); // get connected cities
//                mainCity.erase(remove(mainCity.begin(), mainCity.end(), '\n'), mainCity.end()); // erase \n
//                vector<string> vec; // vector to store connected cities
//                istringstream stringStream(cities);
//                while (!stringStream.eof()) {
//                    getline(stringStream, city, ' ');
//                    vec.insert(vec.begin(), city);
//                }
//                cityToString[(City) enumIndex] = mainCity;
//                stringToCity[mainCity] = (City)enumIndex;
//                connections[mainCity] = make_tuple(color, vec);
//                enumIndex++;
//            }
//        }
//        for (auto &val : cityToString) {
//            diseases[val.first] = 0;
//        }
//    }