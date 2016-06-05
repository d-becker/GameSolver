#ifndef GS_FIRST_STAGE_HPP
#define GS_FIRST_STAGE_HPP

#include <cstddef>
#include <memory>
#include <vector>

#include "GameSolver/GameState.hpp"
#include "GameSolver/GSTypes.hpp"
#include "GameSolver/TreeNode.hpp"

namespace gs {

/**
 * This interface is used in the first stage of the game solving algorithm.
 * This stage is a game tree search with alpha-beta pruning.
 *
 * In the future, caching (transposition table) and multithreading support may
 * be added.
 */
class FirstStage {

private:
	TreeNode alpha_beta_pure(std::shared_ptr<GameState> game_state,
				 size_t depth,
				 eval_type alpha,
				 eval_type beta,
				 bool maximizing) const;
};

} // namespace gs

#endif // GS_FIRST_STAGE_HPP
