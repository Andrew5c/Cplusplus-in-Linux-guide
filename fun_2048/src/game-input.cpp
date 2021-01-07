#include "game-input.hpp"
#include "global.hpp"

namespace Game {
    namespace Input {
        bool checkInputANSI(char c, intended_move_t &intendedmove) {
            using namespace Keypress::Code;
            // TODO:两个触发条件是什么鬼?
            if(c == CODE_ANSI_TRIGGER_1) {
                getKeypressDownInput(c);
                if(c == CODE_ANSI_TRIGGER_2) {
                    getKeypressDownInput(c);
                    switch (c) {
                    case CODE_ANSI_UP:
                        intendedmove[FLAG_MOVE_UP] = true;
                        return false;
                    case CODE_ANSI_DOWN:
                        intendedmove[FLAG_MOVE_DOWN] = true;
                        return false;
                    case CODE_ANSI_RIGHT:
                        intendedmove[FLAG_MOVE_RIGHT] = true;
                        return false;
                    case CODE_ANSI_LEFT:
                        intendedmove[FLAG_MOVE_LEFT] = true;
                        return false;
                    }
                }
            }
            return true;
        }

    } // namespace Input
} // namespace Game