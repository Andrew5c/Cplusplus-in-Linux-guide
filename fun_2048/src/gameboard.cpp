#include "gameboard.hpp"


namespace Game
{
    namespace {
        class RandInt {

        };
        using gameboard_data_array_t = gameBoard::gameboard_data_tuple_t;


        // 判断当前游戏面板中是否还可以进行移动
        bool canMoveOnGameBoardDataArray(gameboard_data_array_t gbda) {

        }

        bool addTileOneGameBoardDataArray(gameboard_data_array_t gbda) {

        }
        
    }
    

    // --------------------------------------------
    // TODO:对上述函数进行重新封装，目的？
    bool addTileOnGameBoard(gameBoard &gb) {
        return addTileOneGameBoardDataArray(gb.gbda);
    }

    long long moveCountOnGameBoard(gameBoard gb) {
        return gb.moveCount;
    }

    bool canMoveOnGameBoard(gameBoard &gb) {
        return canMoveOnGameBoardDataArray(gb.gbda);
    }
} // namespace Game
