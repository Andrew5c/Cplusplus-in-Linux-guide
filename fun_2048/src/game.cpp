#include "game.hpp"
#include "gameboard.hpp"
#include "global.hpp"
#include "game-graphics.hpp"
#include "gameboard-graphics.hpp"
#include "game-pregamemenu.hpp"
#include "game-input.hpp"

#include <array>
#include <chrono>
#include <iostream>
#include <sstream>

namespace Game
{
    namespace
    {
        // 全局变量定义
        enum directions {UP, DOWN, RIGHT, LEFT};
        enum gameStatusFlag { FLAG_WIN,
                              FLAG_END_GAME,
                              FLAG_ONE_SHOT,
                              FLAG_INPUT_ERROR,
                              MAX_NO_GAME_STATUS_FLAGS
        };
        // 指示当前游戏状态
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
        using bool_gameboard_t = std::tuple<bool, gameBoard>;

        // 游戏状态，游戏面板共同打包
        using game_status_board_t = std::tuple<game_status_t, gameBoard>;
        using intendedmove_gamestatus_t = std::tuple<Input::intended_move_t, game_status_t>;
        // -----------------------------------------------------

        // 绘制游戏面板所需要的字符
        std::string drawGraphics(current_game_session_t cgs) {

        }

        game_status_t updateOneShotDisplayFlags(game_status_t gamestatus) {
            const auto disable_one_shot_flag = [](bool &trigger) {trigger = !trigger;};
            if(gamestatus[FLAG_ONE_SHOT]) {
                disable_one_shot_flag(gamestatus[FLAG_ONE_SHOT]);

                if(gamestatus[FLAG_INPUT_ERROR]) {
                    disable_one_shot_flag(gamestatus[FLAG_INPUT_ERROR]);
                }
            }
            return gamestatus;
        }

        // 接收玩家的输入并处理当前游戏状态
        intendedmove_gamestatus_t receiveAgentInput(Input::intended_move_t intendedmove, 
                                                    game_status_t gamestatus) {
            using namespace Input;
            const bool game_still_in_play = !gamestatus[FLAG_END_GAME] && !gamestatus[FLAG_WIN];
            if(game_still_in_play) {
                // 游戏仍在进行，接收玩家输入，开始下一次循环刷新
                char c;
                getKeypressDownInput(c);
                // 检查输入是否合法,只有输入为四个箭头中的其中一个,才合法
                const auto is_invalid_keypress_code = checkInputANSI(c, intendedmove);
                // TODO:检测其他按键的信号,并做相应处理
                // ...

                if(is_invalid_keypress_code) {
                    gamestatus[FLAG_INPUT_ERROR] = true;
                }
            }
            return std::make_tuple(intendedmove, gamestatus);
        }

        // 根据用户的方向键,计算游戏面板数据
        gameBoard decideMove(directions d, gameBoard gb) {
            switch (d) {
            case UP:
                tumbleTilesUpOnGameboard(gb);
                break;

            case DOWN:
                tumbleTilesDownOnGameboard(gb);
                break;

            case LEFT:
                tumbleTilesLeftOnGameboard(gb);
                break;

            case RIGHT:
                tumbleTilesRightOnGameboard(gb);
                break;
            }
            return gb;
        }

        bool_gameboard_t processAgentInput(Input::intended_move_t intendedmove, gameBoard gb) {
            using namespace Input;
            if(intendedmove[FLAG_MOVE_LEFT]) {
                gb = decideMove(LEFT, gb);
            }
            if(intendedmove[FLAG_MOVE_RIGHT]) {
                gb = decideMove(RIGHT, gb);
            }
            if(intendedmove[FLAG_MOVE_UP]) {
                gb = decideMove(UP, gb);
            }
            if(intendedmove[FLAG_MOVE_DOWN]) {
                gb = decideMove(DOWN, gb);
            }
            return std::make_tuple(true, gb);
        }

        // 游戏主逻辑
        game_status_board_t processGameLogic(game_status_board_t gsgb) {
            game_status_t game_status;
            gameBoard gb;
            // 将形参数据拷贝到函数内再使用，而不是直接使用形参数据!
            std::tie(game_status, gb) = gsgb;

            unblockTilesOnGameBoard(gb);

            // 玩家进行了移动
            if(gb.moved) {
                addTileOnGameBoard(gb);
                registerMoveByOneOnGameBoard(gb);
            }
            // TODO：在endless模式下，判断是否达到2048？

            // 游戏面板已经无法进行移动 -> 游戏结束
            if(!canMoveOnGameBoard(gb)) {
                game_status[FLAG_END_GAME] = true;
            }
            return std::make_tuple(game_status, gb);
        }


        // 对游戏结束时的 数据进行收集、整理、打包
        Graphics::scoreboard_display_data_t 
        makeScoreboardDisplayData(ull best_score, gameBoard gb) {
            const auto game_board_score = gb.score;
            const auto temp_best_score = (best_score > game_board_score) ? best_score : game_board_score;
            const auto move_count = moveCountOnGameBoard(gb);
            
            const auto scdd = std::make_tuple(std::to_string(game_board_score), 
                    std::to_string(temp_best_score), std::to_string(move_count));
            return scdd;
        }

        bool_gameboard_t processGameStatus(game_status_board_t gsgb) {

        }

        
        // 单次游戏循环
        bool_current_game_session_t soloGameLoop(current_game_session_t cgs) {
            using namespace Input;
            using tup_idx = tuple_cgs_t_idx;

            // 提取形参的数据的地址
            const auto game_status = std::addressof(std::get<tup_idx::IDX_GAMESTATUS>(cgs));
            const auto gb = std::addressof(std::get<tup_idx::IDX_GAMEBOARD>(cgs));

            // 用户每移动一次，就处理一次游戏逻辑，并返回当前游戏状态
            std::tie(*game_status, *gb) = processGameLogic(std::make_tuple(*game_status, *gb));
            
            // 玩家每次移动后都需要重新更新游戏面板
            drawAlways(std::cout, dataSuppliment(cgs, drawGraphics));
            // 根据用户的输入，更新需要显示的标志位
            *game_status = updateOneShotDisplayFlags(*game_status);

            intended_move_t player_intended_move{};
            // 接收玩家的输入
            std::tie(player_intended_move, *game_status) = 
                receiveAgentInput(player_intended_move, *game_status);
            std::tie(std::ignore, *gb) = processAgentInput(player_intended_move, *gb);

            // 处理游戏状态
            bool loop_again;
            std::tie(loop_again, *game_status) = 
                processGameStatus(std::make_tuple(*game_status, *gb));
            
            return std::make_tuple(loop_again, cgs);
        }

        // 绘制游戏结束界面
        std::string drawEndGameLoopGraphics(current_game_session_t final_game_status) {
            // 按照特定顺序输出界面信息
            using namespace Graphics;
            using namespace GameBoard::Graphics;
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
            // 将游戏结束界面(包含最终游戏状态)定向到标准输出设备
            drawAlways(std::cout, dataSuppliment(current_game_status, drawEndGameLoopGraphics));
            return gb;
        }
    } // namespace

    void playGame(playGameFlag cont, gameBoard gb, ull game_board_size) {
        const auto is_this_a_new_game = (cont == playGameFlag::brandNewGame);
        // TODO:添加每次游戏的统计功能,记录最高分
        // const auto bestScore = statistics::loadGameBestScore();
        const auto bestScore = 100;
        
        // 绘制游戏面板大小：4x4
        if(is_this_a_new_game) {
            // 定义并初始化一个新的游戏面板
            gb = gameBoard(game_board_size);
            addTileOnGameBoard(gb);
        }

        const auto startTime = std::chrono::high_resolution_clock::now();
        gb = endlessGameLoop(bestScore, gb);
        const auto finishTime = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> elapsed = finishTime - startTime;
        const auto duration = elapsed.count();

        // TODO:记录本次游戏最终分数gb,并保存
    }


    void startGame() {
        // TODO:为了保证能够继续之前的游戏,会根据有无存档标志来判断是否继续之前的游戏
        // TODO:一旦选择无存档游戏,程序会进入一个死循环,这里有待改进
        PreGameSetup::setupNewGame();
    }

    void continueGame() {
        PreGameSetup::continueOldGame();
    }
} // namespace Game
