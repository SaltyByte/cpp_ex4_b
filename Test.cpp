#include "doctest.h"
#include <iostream>
#include <stdexcept>



#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

#include "Researcher.hpp"
#include "Scientist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"

using namespace pandemic;
using namespace std;

TEST_CASE("Player Tests") {
    Board board;
    board[City::BuenosAires] = 1;

    Researcher player {board, City::Atlanta};
    player.take_card(City::Karachi)
            .take_card(City::Lagos)
            .take_card(City::Manila)
            .take_card(City::BuenosAires)
            .take_card(City::HoChiMinhCity);

    CHECK(player.role() == "Researcher");
    CHECK_THROWS(player.drive(City::Karachi));
    CHECK_THROWS(player.drive(City::Khartoum));
    CHECK_THROWS(player.drive(City::Kinshasa));
    CHECK_THROWS(player.drive(City::Lima));
    CHECK_THROWS(player.drive(City::Riyadh));
    CHECK_NOTHROW(player.drive(City::Miami));
    CHECK_THROWS(player.drive(City::Miami));
    player.drive(City::Bogota);
    player.drive(City::BuenosAires);
    player.build(); // build in Buenos Aires
    player.drive(City::SaoPaulo);
    CHECK_THROWS(player.fly_direct(City::BuenosAires));
    player.take_card(City::SaoPaulo);
    player.take_card(City::Johannesburg);
    player.take_card(City::Khartoum);
    player.take_card(City::Kinshasa);
    player.take_card(City::Miami);
    player.treat(City::SaoPaulo);

    CHECK_THROWS(player.drive(City::Riyadh));
    CHECK_THROWS(player.drive(City::Paris));
    CHECK_THROWS(player.drive(City::Osaka));
    CHECK_THROWS(player.drive(City::Mumbai));
    CHECK_THROWS(player.drive(City::Montreal));
    CHECK_NOTHROW(player.drive(City::Lagos));

    CHECK_NOTHROW(player.fly_shuttle(City::BuenosAires));
    CHECK_THROWS(player.build()); // cant build in Buenos Aires, already built
    CHECK_NOTHROW(player.take_card(City::Bogota)
          .take_card(City::Johannesburg)
          .take_card(City::Khartoum)
          .take_card(City::Kinshasa)
          .take_card(City::Lima)
          .take_card(City::Lima));
    CHECK_NOTHROW(player.discover_cure(Color::Yellow));
    CHECK_NOTHROW(player.discover_cure(Color::Yellow));



}
TEST_CASE("Jobs Test") {
    Board board;
    Researcher researcher {board, City::Algiers};
    Scientist scientist {board, City::Atlanta, 4};
    FieldDoctor fieldDoctor {board, City::Baghdad};
    GeneSplicer geneSplicer {board, City::Bangkok};
    OperationsExpert operationsExpert {board, City::Beijing};
    Dispatcher dispatcher {board, City::Bogota};
    Medic medic {board, City::BuenosAires};
    Virologist virologist {board, City::Cairo};

    researcher.take_card(City::Baghdad)
              .take_card(City::Algiers)
              .take_card(City::Cairo)
              .take_card(City::Chennai)
              .take_card(City::Delhi);
    CHECK_NOTHROW(researcher.discover_cure(Color::Black)); // can do without research center

    scientist.take_card(City::Atlanta); // not finished


}

TEST_CASE("Board Tests") {
    Board board;
    CHECK(board.is_clean());
    board[City::Kinshasa] = 3;
    board[City::Kinshasa] = 2;
    board[City::MexicoCity] = 3;
    board[City::HoChiMinhCity] = 1;
    board[City::Chicago] = 1;

    GeneSplicer player {board, City::Kinshasa};
    CHECK(player.role() == "GeneSplicer");
    player.take_card(City::MexicoCity)
            .take_card(City::HoChiMinhCity)
            .take_card(City::Chicago);
    player.treat(City::Kinshasa);
    player.treat(City::Kinshasa);
    player.fly_direct(City::MexicoCity);
    player.treat(City::MexicoCity);
    player.treat(City::MexicoCity);
    player.treat(City::MexicoCity);
    CHECK_THROWS(player.treat(City::MexicoCity));
    player.fly_direct(City::HoChiMinhCity);
    CHECK_THROWS(player.fly_direct(City::HoChiMinhCity));
    player.treat(City::HoChiMinhCity);
    player.fly_direct(City::Chicago);
    CHECK_FALSE(board.is_clean());
    player.treat(City::Chicago);
    CHECK(board.is_clean());


}
