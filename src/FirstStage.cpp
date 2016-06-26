#include "FirstStage.hpp"

namespace gs {

std::shared_ptr<TreeNode> FirstStage::alpha_beta_pure(
	                                std::shared_ptr<GameState> game_state,
					size_t depth,
					eval_type alpha,
					eval_type beta,
					bool maximizing) const
{
	static const std::vector< std::shared_ptr<TreeNode> > empty_child_vec{};
	
        if (!game_state) {
		return std::make_shared<TreeNode>(game_state, 0,
						  maximizing, empty_child_vec);
	}

	if (depth == 0) {
		return  std::make_shared<TreeNode>(game_state,
						   game_state->evaluate(),
						   maximizing, empty_child_vec);
	}

	/*if (game_state != GameState.NONE) {
		eval_type value = game_state->evaluate();
		return std::make_shared<TreeNode>(game_state, value
	}*/
}
  
} // namespace gs
