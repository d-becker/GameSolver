#include "FirstStage.hpp"

namespace gs {

namespace /* anonymous */ {

std::shared_ptr<TreeNode> alpha_beta_pure_proper(
	                                std::shared_ptr<GameState> game_state,
					size_t depth,
					eval_type alpha,
					eval_type beta,
					bool maximizing)
{
	std::vector< std::shared_ptr<GameState> > next_states
		= game_state->generate_next_states();
	return nullptr;
}

} // anonymous namespace

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

	if (depth == 0 || game_state->get_winner() != GameState::NONE) {
		return  std::make_shared<TreeNode>(game_state,
						   game_state->evaluate(),
						   maximizing, empty_child_vec);
	}

	// TODO.
	return alpha_beta_pure_proper(game_state, depth,
				      alpha, beta, maximizing);
}
  
} // namespace gs
