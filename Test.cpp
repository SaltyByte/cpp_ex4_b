#include "doctest.h"

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

    CHECK_THROWS(player.drive(City::Karachi));
    CHECK_THROWS(player.drive(City::Khartoum));
    CHECK_THROWS(player.drive(City::Kinshasa));
    CHECK_THROWS(player.drive(City::Lima));
    CHECK_THROWS(player.drive(City::Riyadh));
    CHECK_NOTHROW(player.drive(City::Miami));
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

    CHECK_THROWS(player.fly_shuttle(City::BuenosAires));
    player.take_card(City::BuenosAires);
    CHECK_NOTHROW(player.fly_direct(City::BuenosAires));
    player.take_card(City::BuenosAires);
    CHECK_NOTHROW(player.build()); // nothing happens, card stays in hand
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
    Board board1;
    Board board2;
    Board board3;
    Board board4;
    Board board5;
    Board board6;
    Board board7;
    Board board8;

    Researcher researcher {board1, City::Algiers};
    Scientist scientist {board2, City::Atlanta, 3};
    FieldDoctor fieldDoctor {board3, City::Baghdad};
    GeneSplicer geneSplicer {board4, City::Bangkok};
    OperationsExpert operationsExpert {board5, City::Beijing};
    Dispatcher dispatcher {board6, City::Beijing};
    Medic medic {board7, City::BuenosAires};
    Virologist virologist {board8, City::Sydney};

    CHECK(researcher.role() == "Researcher");
    CHECK(scientist.role() == "Scientist");
    CHECK(fieldDoctor.role() == "FieldDoctor");
    CHECK(geneSplicer.role() == "GeneSplicer");
    CHECK(operationsExpert.role() == "OperationsExpert");
    CHECK(dispatcher.role() == "Dispatcher");
    CHECK(medic.role() == "Medic");
    CHECK(virologist.role() == "Virologist");



    researcher.take_card(City::Baghdad)
              .take_card(City::Algiers)
              .take_card(City::Cairo)
              .take_card(City::Chennai)
              .take_card(City::Delhi);
    CHECK_NOTHROW(researcher.discover_cure(Color::Black)); // can do without research center


    scientist.take_card(City::Atlanta)
             .take_card(City::Chicago)
             .take_card(City::Essen)
             .take_card(City::Atlanta);
    scientist.build();
    CHECK_NOTHROW(scientist.discover_cure(Color::Blue)); // can cure with n=3 cards (from constructor)


    board3[City::Cairo] = 2;
    CHECK_NOTHROW(fieldDoctor.treat(City::Cairo)); // can treat adjacent city no throwing cards
    CHECK(board3[City::Cairo] == 1);


    geneSplicer.take_card(City::Bangkok)
               .take_card(City::Bogota)
               .take_card(City::BuenosAires)
               .take_card(City::Cairo)
               .take_card(City::Chennai);
    CHECK_NOTHROW(geneSplicer.discover_cure(Color::Red)); // should cure with any 5 cards


    CHECK_NOTHROW(operationsExpert.build()); // can build with no card in hand

    dispatcher.take_card(City::Beijing);
    dispatcher.build();
    CHECK_NOTHROW(dispatcher.fly_direct(City::Miami)); // can fly wherever he wants when flying from city with research station


    board7[City::BuenosAires] = 4;
    CHECK_NOTHROW(medic.treat(City::BuenosAires)); // when treating, lowering to 0
    CHECK(board7.is_clean());


    board8[City::SanFrancisco] = 3;
    virologist.take_card(City::SanFrancisco);
    CHECK_NOTHROW(virologist.treat(City::SanFrancisco)); // can treat wherever he is as lost he got the card of the city
    CHECK(board8[City::SanFrancisco] == 2);
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
    player.take_card(City::MexicoCity)
          .take_card(City::HoChiMinhCity)
          .take_card(City::Chicago);
    player.treat(City::Kinshasa);
    player.treat(City::Kinshasa);
    CHECK(board[City::Kinshasa] == 0);
    player.fly_direct(City::MexicoCity);
    player.treat(City::MexicoCity);
    player.treat(City::MexicoCity);
    player.treat(City::MexicoCity);
    CHECK(board[City::MexicoCity] == 0);
    player.fly_direct(City::HoChiMinhCity);
    CHECK_THROWS(player.fly_direct(City::HoChiMinhCity));
    player.treat(City::HoChiMinhCity);
    CHECK(board[City::HoChiMinhCity] == 0);
    player.fly_direct(City::Chicago);
    CHECK_FALSE(board.is_clean());
    player.treat(City::Chicago);
    CHECK(board[City::Chicago] == 0);
    CHECK(board.is_clean());
}
