#include <gtest/gtest.h>

#include "GameSolver/FirstStage.hpp"
#include "TicTacGameState.hpp"

#include <iostream>
#include <fstream>

TEST(TestingTest, TT) {
	using namespace std;
	TicTacGameState game(3, 3, 3);
	cout << "Original: " << endl;
	game.dump();

	game.move(0, 0);
	cout << "After move: " << endl;
	game.dump();

	game.move(2, 2);
	cout << "After move: " << endl;
	game.dump();

	ofstream out("test_log.txt");
	int counter = 1;
	auto states = game.generate_next_states();
	for (auto ptr : states) {
		out << "State " << counter << ":\n";
		TicTacGameState *state = static_cast<TicTacGameState*>(ptr.get());
	        state->dump(out);
		out << "\n";
		++counter;
	}

	FAIL();
}
