#ifndef GS_TREE_NODE_HPP
#define GS_TREE_NODE_HPP

#include <algorithm>
#include <memory>
#include <vector>

#include "GameSolver/GameState.hpp"
#include "GameSolver/GSTypes.hpp"

namespace gs {

/**
 * A tree of \c TreeNode objects is used to store information about the game
 * tree that has been searched during the first stage of the game solver
 * algorithm. This information can later be used to optimize the order of
 * deeper searches.
 */
class TreeNode {
public:
	/**
	 * Constructs a new \c TreeNode.
	 *
	 * \param state The game state of this node.
	 *
	 * \param value The value of the game state at this node.
	 * \param maximizing \c true if the player to move at this stage is
	 *        the maximizing player.
	 * \param children The nodes that can be reached by taking the possible
	 *        moves from the state of this node.
	 * \param sort If this is \c true, the children will be sorted for
	 *        optimization in later tree searches.
	 */
	TreeNode(const std::shared_ptr<const GameState> state,
		 eval_type value,
		 bool maximizing,
		 std::vector< std::shared_ptr<TreeNode> > children,
		 bool sort = true);
	
        const std::shared_ptr<const GameState> state;
	const eval_type value;
	const bool maximizing; // If the player to move at this stage is the
	                       // maximizing player.

	const bool sorted;
	const std::vector< std::shared_ptr<TreeNode> > children;

private:
        
};

/**
 * Checks if two trees of \c TreeNode elements are equal. Two trees are
 * considered equal iff nodes in the two trees pairwise contain the same data
 * (state, value, player and sorting information) and the relations between the
 * nodes also match.
 *
 * \param lhs The root of the first tree.
 * \param rhs The root of the second tree.
 *
 * \return \c true if the two trees are equal; \c false otherwise.
 */
/*bool trees_equal(std::shared_ptr<TreeNode> lhs,
		 std::shared_ptr<TreeNode> rhs);*/

} // namespace gs

#endif // GS_TREE_NODE_HPP
