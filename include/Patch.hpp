#ifndef GS_PATCH_HPP
#define GS_PATCH_HPP

namespace gs {

/**
 * Specializations of this class template hold information about a move of the
 * game. These patches can be applied or reverted by the appropriate
 * instantiation of the \c GameState interface.
 *
 * This class template is intended to be explicitly specialized.
 *
 * \param Resource The type of the resource that holds information of the state
 *        of the game on which this patch can be applied.
 */
template <typename Resource>
struct Patch {
};

} // namespace gs

#endif // GS_PATCH_HPP
