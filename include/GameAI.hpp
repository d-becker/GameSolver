#ifndef GS_GAME_AI_HPP
#define GS_GAME_AI_HPP

#include <memory>

namespace gs {

/**
 * // TODO
 */
class GameAI {
private:
	std::shared_ptr<TreeSearch> m_tree_search;
	std::shared_ptr<FastSearch> m_fast_search;
};

} // namespace gs

#endif // GS_GAME_AI_HPP
