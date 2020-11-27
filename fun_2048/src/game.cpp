#include "game.hpp"
#include "gameboard.hpp"
#include "global.hpp"
#include "game-pregamemenu.hpp"

#include <array>
#include <chrono>
#include <iostream>
#include <sstream>

namespace Game
{

    gameBoard endlessGameLoop() {


    }

    void playGame(playGameFlag cont, gameBoard gb, ull game_board_size) {
        const auto is_this_a_new_game = (cont == playGameFlag::brandNewGame);
        const auto bestScore = statistics::loadGameBestScore();

        if(is_this_a_new_game) {
            gb = gameBoard(game_board_size);
            addTileGameBoard(gb);
        }

        const auto startTime = std::chrono::high_resolution_clock::now();
        gb = endlessGameLoop(bestScore, gb);
    }


    void startGame() {
        // TODO:为了保证能够继续之前的游戏
        // 会根据有无存档标志来判断是否继续之前的游戏
        PreGameSetup::setupNewGame();
    }

    void continueGame() {
        PreGameSetup::continueOldGame();
    }
} // namespace Game
