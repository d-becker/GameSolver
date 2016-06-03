#include "GameSolver/TreeNode.hpp"

namespace /* anonymous */ {

std::vector< std::shared_ptr<gs::TreeNode> >
sorted_vector(std::vector< std::shared_ptr<gs::TreeNode> > children,
	      bool maximizing) {
	using namespace gs;
	
	auto cmp = [=](std::shared_ptr<TreeNode> child1,
		       std::shared_ptr<TreeNode> child2) -> bool {
		if (child1 && child2) {
			if (maximizing) {
				return child1->value > child2->value;
			} else {
				return child1->value < child2->value;
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

} // anonymous namespace

namespace gs {

TreeNode::TreeNode(const std::shared_ptr<const GameState> state,
		   eval_type value,
		   bool maximizing,
		   std::vector< std::shared_ptr<TreeNode> > children,
		   bool sort)
	: state(state),
	  value(value),
	  maximizing(maximizing),
	  sorted(sort),
	  children(sort ? sorted_vector(children, maximizing) : children)
{
}

} // namespace gs
