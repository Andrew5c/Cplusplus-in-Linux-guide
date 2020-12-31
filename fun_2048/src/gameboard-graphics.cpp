#include "gameboard-graphics.hpp"
#include "gameboard.hpp"


#include <array>
#include <sstream>
#include <algorithm>

namespace Game {
    
    namespace GameBoard {
        namespace Graphics {
            namespace {

                std::string drawSelf(gameBoard::gameboard_data_tuple_t gbda) {
                    std::ostringstream str_os;


                    return str_os.str();
                }
            } // namespace

            std::string gameBoardTextOutput(gameBoard gb) {
                return drawSelf(gb.gbda);
            }
        } // namespace Graphics
    }// namespace Gameboard
}// namespace Game
