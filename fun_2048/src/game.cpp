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
        // 全局变量定义
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
        // 对上面游戏会话的抽象数据进行索引
        enum tuple_cgs_t_idx {IDX_BESTSCORE,
                              IDX_GAMESTATUS,
                              IDX_GAMEBOARD
        };
        
        // 当前游戏会话的进一步数据抽象
        using bool_current_game_session_t = std::tuple<bool, current_game_session_t >;
        
        // 游戏状态，游戏面板共同打包
        using game_status_board_t = std::tuple<game_status_t, gameBoard>;
        
        // -----------------------------------------------------

        // 游戏主逻辑
        game_status_board_t processGameLogic(game_status_board_t gsgb) {
            game_status_t game_status;
            gameBoard gb;
            // 将形参数据拷贝到函数内再使用，而不是直接使用形参数据!
            std::tie(game_status, gb) = gsgb;

            unblockTilesOnGameBoard(gb);

            if(gb.moved) {
                addTileOnGameBoard(gb);
            }
            if(!canMoveOnGameBoard(gb)) {
                game_status[FLAG_END_GAME] = true;
            }
            return std::make_tuple(game_status, gb);
        }


        // 对游戏结束时的 数据 进行收集、整理、打包
        Graphics::scoreboard_display_data_t 
        makeScoreboardDisplayData(ull best_score, gameBoard gb) {
            const auto game_board_score = gb.score;
            const auto temp_best_score = (best_score > game_board_score) ? best_score : game_board_score;
            const auto move_count = moveCountOnGameBoard(gb);
            
            const auto scdd = std::make_tuple(std::to_string(game_board_score), 
                    std::to_string(temp_best_score), std::to_string(move_count));
            return scdd;
        }


        // 单次游戏循环
        bool_current_game_session_t soloGameLoop(current_game_session_t cgs) {
            using namespace Input;
            using tup_idx = tuple_cgs_t_idx;

            // 提取形参的数据
            const auto game_status = std::addressof(std::get<tup_idx::IDX_GAMESTATUS>(cgs));
            const auto gb = std::addressof(std::get<tup_idx::IDX_GAMEBOARD>(cgs));

            std::tie(*game_status, *gb) = processGameLogic(std::make_tuple(*game_status, *gb));

        }

        // 绘制游戏结束界面
        std::string drawEndGameLoopGraphics(current_game_session_t final_game_status) {
            // 按照特定顺序输出界面信息
            using namespace Graphics;
            using namespcace gameBoard::Graphics;
            using tup_idx = tuple_cgs_t_idx;
            // 提取元组的内容
            const auto best_score = std::get<tup_idx::IDX_BESTSCORE>(final_game_status);
            const auto end_game_status = std::get<tup_idx::IDX_GAMESTATUS>(final_game_status);
            const auto gb = std::get<tup_idx::IDX_GAMEBOARD>(final_game_status);
            
            std::ostringstream str_os;

            cleanScreen();
            // TODO:这里用定向输出符号应该也可以
            drawAlways(str_os, asciiArt2048);

            // 绘制计分板,scdd是对计分板要显示的数据进行打包
            const auto scdd = makeScoreboardDisplayData(best_score, gb);
            drawAlways(str_os, dataSuppliment(scdd, gameScoreBoardOverlay));

            // TODO:绘制快照在游戏结束
            drawAlways(str_os, dataSuppliment(gb, gameBoardTextOutput));

            // 在竞赛模式下面，当游戏结束的时候绘制 输\赢 提示
            // TODO:竞赛模式暂时去掉

            return str_os.str();
        }

        // 游戏主循环
        gameBoard endlessGameLoop(ull currentBestScore, gameBoard gb) {
            auto loop_again{true};
            auto current_game_status = std::make_tuple(currentBestScore, game_status_t{}, gb);
            while(loop_again) {
                std::tie(loop_again, current_game_status) = soloGameLoop(current_game_status);
            }
            // 将游戏结束界面定向到标准输出设备
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
