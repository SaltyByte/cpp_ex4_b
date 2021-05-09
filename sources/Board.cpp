#include "Board.hpp"
#include <string>
#include <sstream>

using namespace std;

namespace pandemic {
    map<City, tuple<Color, set<City>, string>> Board::connections; // static because we need to read only 1 times.

    Board::Board() {
        if (connections.empty()) {
            initBoard();
        }
        for (const auto &val : connections) {
            diseases[val.first] = 0;
        }
    }
    string Board::getCityString(City city){
        return get<2>(connections[city]);
    }

    void Board::setCure(Color color) {
        cures.insert(color); // possible because set does not allow cuplicates
    }

    int &Board::operator[](City city) {
        return diseases[city];
    }

    ostream &operator<<(ostream &os, const Board &b) {
        os << "Research centers built: " << b.researchStation.size() << endl;
        for (const auto &val : b.researchStation) {
            os << "Research centers at cities: " << Board::getCityString(val) << endl;
        }
        os << "Cures discovers: " << b.cures.size() << endl;
        for (const auto &color : b.cures) {
            os << "Color of cure: " << Board::getColorString(color) << endl;
        }
        int infectedCities = 0;
        for (const auto &val : b.diseases) {
            if (val.second > 0){
                os << "City: " << Board::getCityString(val.first) << ", Number of diseases: " << val.second << endl;
                infectedCities++;
            }
        }
        os << "Number of Cities infected: " << infectedCities << endl;
        return os;
    }

    bool Board::is_clean() {
        for (const auto &var : diseases) {
            if (var.second > 0) {
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
        cures.clear();
    }

    void Board::remove_stations() {
        researchStation.clear();
    }
    bool Board::isResearchStation(City city) {
        return researchStation.find(city) != researchStation.end();
    }
    bool Board::isCured(Color color) {
        return cures.find(color) != cures.end();
    }

    set<City> Board::getNeighbors(City city) {
        return get<1>(connections[city]);
    }

    Color Board::getColor(City city) {
        return get<0>(connections[city]);
    }
    std::string Board::getColorString(Color color) {
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

    void Board::initBoard(){
        connections[City::Algiers] = make_tuple(Color::Black, set<City>{City::Madrid, City::Paris, City::Istanbul, City::Cairo}, "Algiers");
        connections[City::Atlanta] = make_tuple(Color::Blue, set<City>{City::Chicago, City::Miami, City::Washington}, "Atlanta");
        connections[City::Baghdad] = make_tuple(Color::Black, set<City>{City::Tehran, City::Istanbul, City::Cairo, City::Riyadh, City::Karachi}, "Baghdad");
        connections[City::Bangkok] = make_tuple(Color::Red, set<City>{City::Kolkata, City::Chennai, City::Jakarta, City::HoChiMinhCity, City::HongKong}, "Bangkok");
        connections[City::Beijing] = make_tuple(Color::Red, set<City>{City::Shanghai, City::Seoul}, "Beijing");
        connections[City::Bogota] = make_tuple(Color::Yellow, set<City>{City::MexicoCity, City::Lima, City::Miami, City::SaoPaulo, City::BuenosAires}, "Bogota");
        connections[City::BuenosAires] = make_tuple(Color::Yellow, set<City>{City::Bogota, City::SaoPaulo}, "BuenosAires");
        connections[City::Cairo] = make_tuple(Color::Black, set<City>{City::Algiers, City::Istanbul, City::Baghdad, City::Khartoum, City::Riyadh}, "Cairo");
        connections[City::Chennai] = make_tuple(Color::Black, set<City>{City::Mumbai, City::Delhi, City::Kolkata, City::Bangkok, City::Jakarta}, "Chennai");
        connections[City::Chicago] = make_tuple(Color::Blue, set<City>{City::SanFrancisco, City::LosAngeles, City::MexicoCity, City::Atlanta, City::Montreal}, "Chicago");

        connections[City::Delhi] = make_tuple(Color::Black, set<City>{City::Tehran, City::Karachi, City::Mumbai, City::Chennai, City::Kolkata}, "Delhi");
        connections[City::Essen] = make_tuple(Color::Blue, set<City>{City::London, City::Paris, City::Milan, City::StPetersburg}, "Essen");
        connections[City::HoChiMinhCity] = make_tuple(Color::Red, set<City>{City::Jakarta, City::Bangkok, City::HongKong, City::Manila}, "HoChiMinhCity");
        connections[City::HongKong] = make_tuple(Color::Red, set<City>{City::Bangkok, City::Kolkata, City::HoChiMinhCity, City::Shanghai, City::Manila, City::Taipei}, "HongKong");
        connections[City::Istanbul] = make_tuple(Color::Black, set<City>{City::Milan, City::Algiers, City::StPetersburg, City::Cairo, City::Baghdad, City::Moscow}, "Istanbul");
        connections[City::Jakarta] = make_tuple(Color::Red, set<City>{City::Chennai, City::Bangkok, City::HoChiMinhCity, City::Sydney},"Jakarta");
        connections[City::Johannesburg] = make_tuple(Color::Yellow, set<City>{City::Kinshasa, City::Khartoum}, "Johannesburg");
        connections[City::Karachi] = make_tuple(Color::Black, set<City>{City::Tehran, City::Baghdad, City::Riyadh, City::Mumbai, City::Delhi}, "Karachi");
        connections[City::Khartoum] = make_tuple(Color::Yellow, set<City>{City::Cairo, City::Lagos, City::Kinshasa, City::Johannesburg}, "Khartoum");
        connections[City::Kinshasa] = make_tuple(Color::Yellow, set<City>{City::Lagos, City::Khartoum, City::Johannesburg}, "Kinshasa");

        connections[City::Kolkata] = make_tuple(Color::Black, set<City>{City::Delhi, City::Chennai, City::Bangkok, City::HongKong}, "Kolkata");
        connections[City::Lagos] = make_tuple(Color::Yellow, set<City>{City::SaoPaulo, City::Khartoum, City::Kinshasa,}, "Lagos");
        connections[City::Lima] = make_tuple(Color::Yellow, set<City>{City::MexicoCity, City::Bogota, City::Santiago,}, "Lima");
        connections[City::London] = make_tuple(Color::Blue, set<City>{City::NewYork, City::Madrid, City::Essen, City::Paris}, "London");
        connections[City::LosAngeles] = make_tuple(Color::Yellow, set<City>{City::SanFrancisco, City::Chicago, City::MexicoCity, City::Sydney}, "LosAngeles");
        connections[City::Madrid] = make_tuple(Color::Blue, set<City>{City::London, City::NewYork, City::Paris, City::SaoPaulo, City::Algiers}, "Madrid");
        connections[City::Manila] = make_tuple(Color::Red, set<City>{City::Taipei, City::SanFrancisco, City::HoChiMinhCity, City::Sydney, City::HongKong}, "Manila");
        connections[City::MexicoCity] = make_tuple(Color::Yellow, set<City>{City::LosAngeles, City::Chicago, City::Miami, City::Lima, City::Bogota}, "MexicoCity");
        connections[City::Miami] = make_tuple(Color::Yellow, set<City>{City::Atlanta, City::MexicoCity, City::Washington, City::Bogota}, "Miami");
        connections[City::Milan] = make_tuple(Color::Blue, set<City>{City::Essen, City::Paris, City::Istanbul}, "Milan");

        connections[City::Montreal] = make_tuple(Color::Blue, set<City>{City::Chicago, City::Washington, City::NewYork}, "Montreal");
        connections[City::Moscow] = make_tuple(Color::Black, set<City>{City::StPetersburg, City::Istanbul, City::Tehran}, "Moscow");
        connections[City::Mumbai] = make_tuple(Color::Black, set<City>{City::Karachi, City::Delhi, City::Chennai}, "Mumbai");
        connections[City::NewYork] = make_tuple(Color::Blue, set<City>{City::Montreal, City::Washington, City::London ,City::Madrid}, "NewYork");
        connections[City::Osaka] = make_tuple(Color::Red, set<City>{City::Taipei, City::Tokyo}, "Osaka");
        connections[City::Paris] = make_tuple(Color::Blue, set<City>{City::Algiers, City::Essen, City::Madrid, City::Milan, City::London}, "Paris");
        connections[City::Riyadh] = make_tuple(Color::Black, set<City>{City::Baghdad, City::Cairo, City::Karachi}, "Riyadh");
        connections[City::SanFrancisco] = make_tuple(Color::Blue, set<City>{City::LosAngeles, City::Chicago, City::Tokyo, City::Manila}, "SanFrancisco");
        connections[City::Santiago] = make_tuple(Color::Yellow, set<City>{City::Lima}, "Santiago");
        connections[City::SaoPaulo] = make_tuple(Color::Yellow, set<City>{City::Bogota, City::BuenosAires, City::Lagos, City::Madrid}, "SaoPaulo");

        connections[City::Seoul] = make_tuple(Color::Red, set<City>{City::Beijing, City::Shanghai, City::Tokyo}, "Seoul");
        connections[City::Shanghai] = make_tuple(Color::Red, set<City>{City::Beijing, City::HongKong, City::Taipei, City::Seoul, City::Tokyo}, "Shanghai");
        connections[City::StPetersburg] = make_tuple(Color::Blue, set<City>{City::Essen, City::Istanbul, City::Moscow}, "StPetersburg");
        connections[City::Sydney] = make_tuple(Color::Red, set<City>{City::Jakarta, City::Manila, City::LosAngeles}, "Sydney");
        connections[City::Taipei] = make_tuple(Color::Red, set<City>{City::Shanghai, City::HongKong, City::Osaka, City::Manila}, "Taipei");
        connections[City::Tehran] = make_tuple(Color::Black, set<City>{City::Baghdad, City::Moscow, City::Karachi, City::Delhi}, "Tehran");
        connections[City::Tokyo] = make_tuple(Color::Red, set<City>{City::Seoul, City::Shanghai, City::Osaka, City::SanFrancisco}, "Tokyo");
        connections[City::Washington] = make_tuple(Color::Blue, set<City>{City::Atlanta, City::NewYork, City::Montreal, City::Miami}, "Washington");
    }
}