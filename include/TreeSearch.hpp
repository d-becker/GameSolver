#ifndef GS_TREE_SEARCH_HPP
#define GS_TREE_SEARCH_HPP

#include <cstddef>
#include <memory>
#include <vector>

#include "GameSolver/GameState.hpp"
#include "GameSolver/Patch.hpp"
#include "GameSolver/TreeNode.hpp"

namespace gs {

/**
 * This interface is used in the first stage of the game solving algorithm.
 * This stage is a game tree search.
 *
 * In the future, caching (transposition table) and multithreading support may
 * be added.
 */
template <typename Resource>
class TreeSearch {
public:
	virtual std::shared_ptr< TreeNode<Resource> >
	search_tree(std::shared_ptr< GameState<Resource> > game_state,
		    std::size_t depth) = 0;
private:
};

} // namespace gs

#endif // GS_TREE_SEARCH_HPP
