#include <gtest/gtest.h>

#include <limits>

#include "GameSolver/FirstStage.hpp"
#include "TicTacGameState.hpp"

#include <iostream>
#include <fstream>

using namespace gs;

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

class FirstStageABTest : public ::testing::Test {
protected:
	FirstStage first_stage;	
};

TEST_F(FirstStageABTest, HeuristicAtLastPly) {	
	std::shared_ptr<TicTacGameState> game =
		std::make_shared<TicTacGameState>(3, 3, 3);
	game->move(0, 0);

	eval_type alpha = std::numeric_limits<eval_type>::lowest();
	eval_type beta = std::numeric_limits<eval_type>::max();

	eval_type heuristic = game->evaluate();
	std::shared_ptr<TreeNode> node =
		first_stage.alpha_beta_pure(game, 0, alpha, beta, true);
	eval_type node_value = node->value;

	ASSERT_EQ(heuristic, node_value);
}
