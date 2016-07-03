#ifndef GS_ALPHA_BETA_HPP
#define GS_ALPHA_BETA_HPP

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
class AlphaBeta {

public:
	std::shared_ptr<TreeNode> alpha_beta_pure(
					std::shared_ptr<GameState> game_state,
					size_t depth,
					eval_type alpha,
					eval_type beta,
					bool maximizing) const;
};

} // namespace gs

#endif // GS_ALPHA_BETA_HPP
