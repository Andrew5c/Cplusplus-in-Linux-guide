#ifndef __GAMEBOARD_H
#define __GAMEBOARD_H

#include "global.hpp"
#include <tuple>
#include <vector>

namespace Game
{
    // 对游戏面板中的每一个小方格的数据抽象
    struct tile_t
    {
        ull value{};
        bool blocked{};
    };
    
    // 整个游戏面板（4x4）的数据抽象
    struct gameBoard
    {
        using tile_data_array_t = std::vector<tile_t>;
        // size_t可以看做是一个unsigned int的数据类型
        using gameboard_data_tuple_t = std::tuple<size_t, tile_data_array_t>;

        gameboard_data_tuple_t gbda;
        // TODO:推测这个win和competition mode有关系，暂时取消
        // bool win{};
        bool moved{true};
        ull score{};
        ull largestTile{2};
        long long moveCount{-1};

        // TODO:结构体的默认构造函数吗?
        gameBoard() = default;
        explicit gameBoard(ull playsize);
        explicit gameBoard(ull playsize, tile_data_array_t prempt_board);
    };

    long long moveCountOnGameBoard(gameBoard gb);
    bool addTileOnGameBoard(gameBoard &gb);
    bool canMoveOnGameBoard(gameBoard &gb);
    
} // namespace Game


#endif