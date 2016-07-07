#ifndef GS_TREE_SEARCH_HPP
#define GS_TREE_SEARCH_HPP

#include <cstddef>
#include <functional>
#include <memory>

#include "GameSolver/GameState.hpp"
#include "GameSolver/GSTypes.hpp"
#include "GameSolver/TreeNode.hpp"

namespace gs {

class TreeSearch {
public:
	virtual std::shared_ptr<TreeNode>
	search_tree(std::shared_ptr<GameState> game_state,
		    size_t depth,
		    bool maximizing,
		    std::function<eval_type(std::shared_ptr<
					    GameState>)> eval) = 0;
};

} // namespace gs

#endif // GS_TREE_SEARCH_HPP
