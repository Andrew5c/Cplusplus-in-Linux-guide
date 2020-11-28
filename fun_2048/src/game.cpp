#include "game.hpp"
#include "gameboard.hpp"
#include "global.hpp"
#include "game-graphics.hpp"
#include "game-pregamemenu.hpp"

#include <array>
#include <chrono>
#include <iostream>
#include <sstream>

namespace Game
{
    namespace
    {
        enum direstion {UP, DOWN, RIGHT, LEFT};
        enum gameStatusFlag { FLAG_WIN,
                              FLAG_END_GAME,
                              FLAG_ONE_SHOT,
                              MAX_NO_GAME_STATUS_FLAGS
        };
        using game_status_t = std::array<bool, MAX_NO_GAME_STATUS_FLAGS>;

        // TODO: 当前游戏会话的数据抽象
        // (best_score, game_status, game_play_board)
        using current_game_session_t = std::tuple<ull, game_status_t, gameBoard>;
        // 对上面游戏会话的抽象数据中进行索引
        enum tuple_cgs_t_idx {IDX_BESTSCORE,
                              IDX_GAMESTATUS,
                              IDX_GAMEBOARD
        };
        
        // 当前游戏会话的进一步数据抽象
        using bool_current_game_session_t = std::tuple<bool, current_game_session_t >;
        
        // 单次游戏循环
        bool_current_game_session_t soloGameLoop(current_game_session_t cgs) {

        }

        // 绘制游戏结束界面
        std::string drawEndGameLoopGraphics(current_game_session_t final_game_status) {
            // 按照特定顺序输出界面信息
            using namespace Graphics;
            using namespcace gameBoard::Graphics;
            using tup_idx = tuple_cgs_t_idx;
            // 读取元组的内容
            const auto best_score = std::get<tup_idx::IDX_BESTSCORE>(final_game_status);

            std::ostringstream str_os;

            cleanScreen();
            // TODO:这里用定向输出符号应该也可以
            drawAlways(str_os, asciiArt2048);

            drawAlways(str_os, );
        }

        // 游戏主循环
        gameBoard endlessGameLoop(ull currentBestScore, gameBoard gb) {
            auto loop_again{true};
            auto current_game_status = std::make_tuple(currentBestScore, game_status_t{}, gb);
            while(loop_again) {
                std::tie(loop_again, current_game_status) = soloGameLoop(current_game_status);
            }
            drawAlways(std::cout, dataSuppliment(current_game_status, drawEndGameLoopGraphics));
            return gb;
        }
    } // namespace

    void playGame(playGameFlag cont, gameBoard gb, ull game_board_size) {
        const auto is_this_a_new_game = (cont == playGameFlag::brandNewGame);
        const auto bestScore = statistics::loadGameBestScore();

        // 绘制游戏面板大小：4x4
        if(is_this_a_new_game) {
            gb = gameBoard(game_board_size);
            addTileOnGameBoard(gb);
        }

        const auto startTime = std::chrono::high_resolution_clock::now();
        gb = endlessGameLoop(bestScore, gb);
        const auto finishTime = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> elapsed = finishTime - startTime;
        const auto duration = elapsed.count();

        // TODO:记录本次游戏最终分数并保存
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
