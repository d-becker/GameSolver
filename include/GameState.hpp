#ifndef GS_GAME_STATE_HPP
#define GS_GAME_STATE_HPP

#include <memory>
#include <vector>

#include "GameSolver/GSTypes.hpp"

namespace gs {

/**
 * This is an interface that contains methods that manupilate and get
 * information about the state of the game.
 */
class GameState {
public:
	enum Result {
		MAXIMIZING,
		MINIMIZING,
		DRAW,
		NONE
	};
	
	/**
	 * Checks whether the game is won. The result is a member of the
	 * enum \c Result.
	 *
	 * \return \c MAXIMIZING if the maximizing player has won;
	 *         \c MINIMIZING if the minimizing player has won;
	 *         \c DRAW if the game has ended with a draw;
	 *         \c NONE if the game is not over.
	 */
	virtual Result get_winner() const = 0;

	/**
	 * Returns a vector containing (smart) pointers to the states that can
	 * be reached from this state by legal moves.
	 *
	 * \return A vector containing (smart) pointers to the states that can
	 *         be reached from this state by legal moves.
	 */
        virtual std::vector< std::shared_ptr<GameState> >
	generate_next_states() const = 0;

	/**
	 * Evaluates the current game state with a heuristic function.
	 *
	 * \return The value of this game state according to a
	 *         heuristic function.
	 *         Positive values are good for the maximizing player,
	 *         negative values for the minimizing player.
	 */
	virtual eval_type evaluate() const = 0;

	/**
	 * Returns a shallow copy of this \c GameState object. The underlying
	 * resources are not (necessarily) copied.
	 *
	 * \return A shallow copy of this \c GameState object.
	 */
	virtual std::shared_ptr<GameState> shallow_copy() const = 0;

	/**
	 * Returns a deep copy of this \c GameState object. All underlying
	 * resources are also deep-copied so that the resulting object is
	 * completely independent of this object.
	 *
	 * \return A deep copy of this \c GameState object.
	 */
	virtual std::shared_ptr<GameState> deep_copy() const = 0;
};
	
} // namespace gs

#endif // GS_GAME_STATE_HPP
