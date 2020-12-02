#include "gameboard.hpp"
#include <algorithm>
#include <array>
#include <chrono>
#include <random>

namespace Game
{
    namespace {
        class RandInt {

        };

        using gameboard_data_array_t = gameBoard::gameboard_data_tuple_t;
        enum gameboard_data_array_fields {IDX_PLAYSIZE,
                                          IDX_BOARD,
                                          MAX_NO_INDEXES};

        // 判断当前游戏面板中是否还可以进行移动
        bool canMoveOnGameBoardDataArray(gameboard_data_array_t gbda) {

        }

        bool addTileOneGameBoardDataArray(gameboard_data_array_t gbda) {

        }

        // 解锁游戏面板中的小方格
        gameboard_data_array_t 
        unblockTilesOnGameBoardDataArray(gameboard_data_array_t gbda) {
            using tile_data_array_t = gameBoard::tile_data_array_t;
            // TODO：这句语法是什么？
            // 初始化一个新的vector，空间是当前游戏面板中的所有小方格数量
            auto new_board_data_array = tile_data_array_t(std::get<IDX_BOARD>(gbda).size());
            // 对形参中的数据进行转换
            std::transform(std::begin(std::get<IDX_BOARD>(gbda)), 
                            std::begin(std::get<IDX_BOARD>(gbda)), 
                            std::begin(new_board_data_array), 
                            [](const tile_t t){
                                return tile_t{t.value, false};
                            });
            return gameboard_data_array_t{std::get<IDX_PLAYSIZE>(gbda), 
                                          new_board_data_array};
        }

        // 判断当前游戏面板是否还可以进行移动
        bool canMoveOnGameBoardDataArray(gameboard_data_array_t gbda) {

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

    void unblockTilesOnGameBoard(gameBoard &gb) {
        gb.gbda = unblockTilesOnGameBoardDataArray(gb.gbda);
    }
} // namespace Game
