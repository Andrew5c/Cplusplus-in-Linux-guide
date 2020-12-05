#ifndef __GAME_INPUT_H
#define __GAME_INPUT_H

#include <array>

namespace Game {
    namespace Input {
        namespace Keypress {
            namespace Code {

            } // namespace Code
        } // namespace Keypress
        enum IntendedMoveFlag {
            FLAG_MOVE_LEFT,
            FLAG_MOVE_RIGHT,
            FLAG_MOVE_UP,
            FLAG_MOVE_DOWN,
            MAX_NO_INTENDED_MOVE_FLAGS
        };
        using intended_move_t = std::array<bool, MAX_NO_INTENDED_MOVE_FLAGS>;

        
    } // namespace Input
} // namespace Game

#endif