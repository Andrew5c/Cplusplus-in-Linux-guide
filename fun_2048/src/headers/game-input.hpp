#ifndef __GAME_INPUT_H
#define __GAME_INPUT_H

#include <array>

namespace Game {
    namespace Input {
        namespace Keypress {
            namespace Code {
                enum {
                    // TODO:这两个枚举的作用是什么?
                    CODE_ESC = 27, 
                    CODE_LSQUAREBRACKET = '[' 
                };
                
                // TODO： 目前只保留对 箭头按键 的支持
                // ANSI格式的 箭头按键为什么是这样的?
                enum {
                    CODE_ANSI_TRIGGER_1 = CODE_ESC,
                    CODE_ANSI_TRIGGER_2 = CODE_LSQUAREBRACKET 
                };
                
                enum {
                    CODE_ANSI_UP = 'A',
                    CODE_ANSI_DOWN = 'B',
                    CODE_ANSI_LEFT = 'D',
                    CODE_ANSI_RIGHT = 'C'
                };

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

        bool checkInputANSI(char c, intended_move_t &intendedmove);
        // bool checkInputVIM(char c, intended_move_t &intendedmove);
        // bool checkInputWASD(char c, intended_move_t &intendedmove);
        
    } // namespace Input
} // namespace Game

#endif