#ifndef GS_EVALUATION_HPP
#define GS_EVALUATION_HPP

#include <memory>

#include "GameSolver/GameState.hpp"
#include "GameSolver/GSTypes.hpp"

namespace gs {

/**
 * This interface is used in the second stage of the game solving algorithm.
 * This stage comes after the game tree search. In this stage, a game state is
 * evaluated in a faster and often less precise way, such as a heuristic
 * function or the Monte Carlo method.
 */
class Evaluation {
public:
	/**
	 * Evaluates the given game state with a fast, for example heuristic or
	 * Monte Carlo method. The time complexity of this method should be
	 * strictly sub-exponential.
	 *
	 * \param game_state The game state to evaluate.
	 *
	 * \return A number describing the value of the game state.
	 *         Positive values are good for the maximizing player,
	 *         negative values for the minimizing player.
	 */
	virtual eval_type
	evaluate(std::shared_ptr<GameState> game_state) const = 0;
};

} // namespace gs

#endif // GS_EVALUATION_HPP
