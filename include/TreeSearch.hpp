#ifndef GS_TREE_SEARCH_HPP
#define GS_TREE_SEARCH_HPP

#include <memory>
#include <vector>

#include "GameSolver/GameState.hpp"
#include "GameSolver/Patch.hpp"
#include "GameSolver/TreeNode.hpp"

namespace gs {

/**
 * This interface is used in the first stage of the game solving algorithm.
 * This stage is a game tree search with alpha-beta pruning.
 *
 * In the future, caching (transposition table) and multithreading support may
 * be added.
 */
template <typename Resource>
class TreeSearch {

private:
};

} // namespace gs

#endif // GS_TREE_SEARCH_HPP
