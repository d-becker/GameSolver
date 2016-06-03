#ifndef GS_GAME_STATE_HPP
#define GS_GAME_STATE_HPP

#include <memory>
#include <vector>

#include "GameSolver/Patch.hpp"

namespace gs {

/**
 * This is an interface that contains methods that manupilate and get
 * information about the state of the game.
 * The class is templated on the underlying resource that holds information
 * about the state of the game.
 *
 * \param Resource The underlying resource that holds information about the
 *        state of the game.
 */
template <typename Resource>
class GameState {
public:
	/**
	 * Applies a move on the game state if it is possible.
	 *
	 * \param move The move to apply.
	 *
	 * \return \c true if the move could be applied; \c false otherwise.
	 */
	virtual bool apply_move(const Patch<Resource>& move) = 0;

	/**
	 * Reverts a move (that is, applies the inverse of the move) if it is
	 * possible. It is not checked whether the given move actually was the
	 * last taken.
	 *
	 * \param move The move to revert.
	 *
	 * \return \c true if the move could be reverted; \c false otherwise.
	 */
	virtual bool revert_move(const Patch<Resource>& move) = 0;

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
	 * Returns a vector containing patches that represent all the legal
	 * moves the actual player can take at this game state.
	 *
	 * \return A vector containing patches that represent all the legal
	 *         moves the actual player can take at this game state.
	 */
	virtual std::vector< Patch<Resource> > generate_moves() const = 0;

	/**
	 * Returns a shallow copy of this \c GameState object. The underlying
	 * resources are not (necessarily) copied.
	 *
	 * \return A shallow copy of this \c GameState object.
	 */
	virtual std::shared_ptr<GameState<Patch<Resource> > >
	shallow_copy() const = 0;

	/**
	 * Returns a deep copy of this \c GameState object. All underlying
	 * resources are also deep-copied so that the resulting object is
	 * completely independent of this object.
	 *
	 * \return A deep copy of this \c GameState object.
	 */
	virtual std::shared_ptr< GameState< Patch<Resource> > >
	deep_copy() const = 0;
};
	
} // namespace gs

#endif // GS_GAME_STATE_HPP
