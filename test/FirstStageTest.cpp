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

	eval_type alpha_start = std::numeric_limits<eval_type>::lowest();
	eval_type beta_start = std::numeric_limits<eval_type>::max();

	std::shared_ptr<TicTacGameState> game =
		std::make_shared<TicTacGameState>(3, 3, 3);
};

TEST_F(FirstStageABTest, ZeroWhenNullPtr) {
	eval_type zero = 0;

	std::shared_ptr<TreeNode> node =
		first_stage.alpha_beta_pure(nullptr, 3, alpha_start,
					    beta_start, true);

	eval_type node_value = node->value;
	ASSERT_EQ(zero, node_value);
}

TEST_F(FirstStageABTest, HeuristicAtLastPly) {
	game->move(0, 0);


	eval_type heuristic = game->evaluate();
	std::shared_ptr<TreeNode> node =
		first_stage.alpha_beta_pure(game, 0, alpha_start,
					    beta_start, true);
	eval_type node_value = node->value;

	ASSERT_EQ(heuristic, node_value);
}

TEST_F(FirstStageABTest, HeuristicOnGameOver) {
	game->move(0, 0);
	game->move(1, 0);

	game->move(0, 1);
	game->move(1, 1);

	game->move(0, 2);

	FAIL();
}
