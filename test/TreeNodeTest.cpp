#include <gtest/gtest.h>

#include "GameSolver/TreeNode.hpp"

using namespace gs;

namespace /* anonymous */ {

/**
 * Mock object for gs::GameState.
 */
class GameStateMock : public gs::GameState {
public:
	virtual Result get_winner() const override {
		return GameState::NONE;
	}

        virtual std::vector< std::shared_ptr<GameState> >
	generate_next_states() const override {
		return {};
	}

	virtual eval_type evaluate() const override {
		return 0;
	}

        virtual std::shared_ptr<GameState> shallow_copy() const override {
		return nullptr;
	}

        virtual std::shared_ptr<GameState> deep_copy() const override {
		return nullptr;
	}
};

// Test fixture
class TreeNodeTest : public ::testing::Test {
protected:
	TreeNodeTest()
		: f_state(std::make_shared<GameStateMock>()),
		  f_value(15),
		  f_maximizing(false),
		  f_sorted(true),
		  f_children({node1, node3, node2} /* Deliberately not sorted*/ )
        {
	}
		  
	
	const std::shared_ptr<const GameStateMock> f_state;
	const gs::eval_type f_value;
	const bool f_maximizing;
	const bool f_sorted;

	// Children
	eval_type val1 = 1;
	eval_type val2 = 2;
	eval_type val3 = 3;

	const std::vector< std::shared_ptr<TreeNode> > empty_vec{};

	std::shared_ptr<TreeNode> node1 =
		std::make_shared<TreeNode>(
			nullptr, val1, false, empty_vec, false);
	std::shared_ptr<TreeNode> node2 =
		std::make_shared<TreeNode>(
			nullptr, val2, false, empty_vec, false);
	std::shared_ptr<TreeNode> node3 =
		std::make_shared<TreeNode>(
			nullptr, val3, false, empty_vec, false);
	
        const std::vector< std::shared_ptr<TreeNode> > f_children;
};

TEST_F(TreeNodeTest, State) {
	TreeNode node(f_state, 2, false, {}, false);
	ASSERT_EQ(f_state, node.state);
}

TEST_F(TreeNodeTest, Value) {
	TreeNode node(f_state, f_value, false, {}, false);
	ASSERT_EQ(f_value, node.value);
}

TEST_F(TreeNodeTest, Maximizing) {
	TreeNode node(f_state, 2, f_maximizing, {}, false);
	ASSERT_EQ(f_maximizing, node.maximizing);
}

TEST_F(TreeNodeTest, Sorted) {
	TreeNode node(f_state, 2, false, {}, f_sorted);
	ASSERT_EQ(f_sorted, node.sorted);
}

TEST_F(TreeNodeTest, ChildrenNoSort) {
	TreeNode node(f_state, 2, false, f_children, false);
	ASSERT_EQ(f_children, node.children);
}

TEST_F(TreeNodeTest, ChildrenMaximSort) {
	TreeNode node(f_state, 2, true, f_children, true);
	const std::vector< std::shared_ptr<TreeNode > > exp_res
	                                               {node3, node2, node1};
	ASSERT_EQ(exp_res, node.children);
}

TEST_F(TreeNodeTest, ChildrenMinimSort) {
	TreeNode node(f_state, 2, false, f_children, true);
	const std::vector< std::shared_ptr<TreeNode> > exp_res
	                                               {node1, node2, node3};
	ASSERT_EQ(exp_res, node.children);
}

} // anonymous namespace
