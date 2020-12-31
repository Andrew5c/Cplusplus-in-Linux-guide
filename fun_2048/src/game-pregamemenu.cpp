#include "game-pregamemenu.hpp"
#include "global.hpp"
#include "game-graphics.hpp"
#include "game.hpp"
#include "gameboard.hpp"

#include <iostream>
#include <array>
#include <sstream>

namespace Game
{
    namespace PreGameSetup
    {
        namespace
        {
            // 暂时取消用户自定义游戏面板大小，固定为 4x4
            // TODO : 后面可以将这个变量设置为宏定义
            ull stored_game_size{4};
            /*
            enum preGameSetupStatusFlag {
                FLAG_NULL,
                FLAG_START_GAME,
                FLAG_RETURN_TO_MAIN_MENU,
                MAX_NO_PREGAME_SETUP_STATUS_FLAGS            
            };
            using pregamesetup_status_t = 
                std::array<bool, MAX_NO_PREGAME_SETUP_STATUS_FLAGS>;
            */
            //bool flagInputErrorChoice{};
            bool noSave{};

            // --------------------------
            
            void processPreGameMenu() {
                playGame(playGameFlag::brandNewGame, gameBoard{stored_game_size}, 
                            stored_game_size);
            }

            void oneLoop() {
                // 这个函数对原始代码做了较大改动,主要原因是删除自定义面板大小的功能
                // 整个屏幕的刷新是通过不断的清屏/打印实现的
                cleanScreen();
                // 绘制游戏启动标题
                drawAlways(std::cout, Graphics::asciiArt2048);
                // 没有游戏存档时，提示用户
                drawOneTimeFlag(std::cout, noSave, Graphics::gameNoSavePrompt);  

                processPreGameMenu();
            }

            void endlessLoop() {
                // TODO:添加游戏中途退出按钮
                // 原始的游戏风格是无限模式,只有用户达到2048,才会出现退出选项
                // 中途想要退出只能强行中断程序
                while(1) {
                    oneLoop();
                }
            }

            enum class newGameFlag {newGameFlagNull, noPreGameSave};
            
            void setupNewGame(newGameFlag ns) {
                // 进入游戏先判断之前有无存档
                // 若没有存档，那么后面当用户选择【继续之前的游戏】时，提示错误。
                noSave = (ns == newGameFlag::noPreGameSave) ? true : false;
                endlessLoop();
            }
        } // namespace
        


        // --------------------------------
        void setupNewGame() {
            // 首次游戏时，初始化为：无存档
            setupNewGame(newGameFlag::newGameFlagNull);
        }

        void continueOldGame() {

        }
    } // namespace PreGameSetup
    
} // namespace Game