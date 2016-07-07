#include "AlphaBeta.hpp"

#include <algorithm>
#include <limits>

namespace gs {

std::shared_ptr<TreeNode>
AlphaBeta::search_tree(std::shared_ptr<GameState> game_state,
		       size_t depth,
		       bool maximizing,
		       std::function<
		           eval_type(std::shared_ptr<GameState>)> eval)
{
	return alpha_beta_pure(game_state, depth,
			       std::numeric_limits<eval_type>::lowest(),
			       std::numeric_limits<eval_type>::max(),
			       maximizing, eval);
}

std::shared_ptr<TreeNode>
AlphaBeta::alpha_beta_pure(std::shared_ptr<GameState> game_state,
			   size_t depth,
			   eval_type alpha,
			   eval_type beta,
			   bool maximizing,
			   std::function<eval_type(
				   std::shared_ptr<GameState>)> eval) const
{
	static const std::vector< std::shared_ptr<TreeNode> > empty_child_vec{};
	
        if (!game_state) {
		return std::make_shared<TreeNode>(game_state, 0,
						  maximizing, empty_child_vec);
	}

	if (depth == 0 || game_state->get_winner() != GameState::NONE) {
		return  std::make_shared<TreeNode>(game_state,
						   eval(game_state),
						   maximizing, empty_child_vec);
	}

	// TODO.
	return alpha_beta_pure_proper(game_state, depth,
				      alpha, beta, maximizing, eval);
}

// Private
std::shared_ptr<TreeNode>
AlphaBeta::alpha_beta_pure_proper(std::shared_ptr<GameState> game_state,
				  size_t depth,
				  eval_type alpha,
				  eval_type beta,
				  bool maximizing,
				  std::function<eval_type(
				      std::shared_ptr<GameState>)> eval) const
{
	std::vector< std::shared_ptr<GameState> > children
		= game_state->generate_next_states();
	std::vector< std::shared_ptr<TreeNode> > child_nodes;

        const eval_type& (*min_or_max) (const eval_type&, const eval_type&);
        if (maximizing) min_or_max = &std::max; else min_or_max = &std::min;
	
	eval_type value = maximizing ? std::numeric_limits<eval_type>::lowest()
		                        : std::numeric_limits<eval_type>::max();

	for (std::shared_ptr<GameState> child : children) {
		std::shared_ptr<TreeNode> child_tree
			= alpha_beta_pure(child, depth - 1, alpha,
					  beta, !maximizing, eval);
		child_nodes.emplace_back(child_tree);

		value = min_or_max(value, child_tree->value);

		if (maximizing)
			alpha = std::max(alpha, value);
		else
			beta = std::min(beta, value);

		if (beta <= alpha)
			break; // Cut-off
	}
	
	return std::make_shared<TreeNode>(game_state, value,
					  maximizing, child_nodes, true);
}
  
} // namespace gs
