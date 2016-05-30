#ifndef GS_TREE_NODE_HPP
#define GS_TREE_NODE_HPP

#include <algorithm>
#include <memory>
#include <vector>

#include "GameSolver/GameState.hpp"
#include "GameSolver/GSTypes.hpp"
#include "GameSolver/Patch.hpp"

namespace gs {

/**
 * A tree of \c TreeNode objects is used to store information about the game
 * tree that has been searched during the first stage of the game solver
 * algorithm. This information can later be used to optimize the order of
 * deeper searches.
 *
 * \param Resource The type of the underlying resource that holds information
 *        about the game state.
 */
template <typename Resource>
class TreeNode {
public:
	/**
	 * Constructs a new \c TreeNode.
	 *
	 * \param patch The patch that has been applied to the parent node's
	 *        state to obtain the state of this node.
	 *
	 * \param alpha The calculated alpha value of the state of the game at
	 *        this node.
	 * \param beta The calculated beta value of the state of the game at
	 *        this node.
	 * \param maximizing \c true if the player to move at this stage is
	 *        the maximizing player.
	 * \param children The nodes that can be reached by taking the possible
	 *        moves from the state of this node.
	 * \param sort If this is \c true, the children will be sorted for
	 *        optimization in later tree searches.
	 */
	TreeNode(Patch<Resource> patch,
		 eval_type alpha,
		 eval_type beta,
		 bool maximizing,
		 std::vector< std::shared_ptr<TreeNode> > children,
		 bool sort = true)
		: patch(patch),
		  alpha(alpha),
		  beta(beta),
		  maximizing(maximizing),
		  children(sort ? sorted_vector(children) : children),
		  sorted(sort)
	{
	}
	
        const Patch<Resource> patch;
	const eval_type alpha;
	const eval_type beta;
	const bool maximizing; // If the player to move at this stage is the
	                       // maximizing player.

	const bool sorted;
	const std::vector< std::shared_ptr<TreeNode> > children;

private:
        std::vector< std::shared_ptr<TreeNode> >
	sorted_vector(std::vector< std::shared_ptr<TreeNode> > children) const {
		auto cmp = [this](std::shared_ptr<TreeNode> child1,
				  std::shared_ptr<TreeNode> child2) -> bool {
			if (child1 && child2) {
			        if (maximizing) {
					return child1->alpha > child2->alpha;
				} else {
					return child1->beta < child2->beta;
				}
			} else if (child1) {
				return true;
			} else {
				return false;
			}
		};

		std::sort(children.begin(), children.end(), cmp);
		return children;
	}
};

} // namespace gs

#endif // GS_TREE_NODE_HPP
