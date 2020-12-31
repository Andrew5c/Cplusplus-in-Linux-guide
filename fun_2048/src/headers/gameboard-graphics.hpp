#ifndef __GAMEBOARD_GRAPHICS_H
#define __GAMEBOARD_GRAPHICS_H

#include <string>

namespace Game {
    struct  gameBoard;
    
    namespace GameBoard {
        namespace Graphics {
            std::string gameBoardTextOutput(gameBoard gb);
        } // namespace Graphics
    } // namespace Gameboard
} // namespace Game


#endif