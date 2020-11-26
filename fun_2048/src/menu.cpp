#include "menu.hpp"
#include "global.hpp"
#include "game.hpp"
#include "game-graphics.hpp"
#include "menu-graphics.hpp"

#include<iostream>
#include<array>
/*
1. 作为整个游戏的入口。并定义游戏的主循环。
*/


// 无名的 命名空间，让其中包含的代码只在本文件可用
namespace {
    // 利用枚举表示状态量，增加程序的可读性
    enum mainMenuStatusFlag {
        FLAG_NULL,
        FLAG_START_GAME,
        FLAG_CONTINUE_GAME,
        FLAG_DISPLAY_HIGHSCORES,
        FLAG_EXIT_GAME,
        // 下面这个标志位没有实际意义，用来计算上面枚举常量的个数
        MAX_NO_MAIN_MENU_STATUS_FLAGS
    };
    // 利用一个bool类型的array容器存储所有的flag
    // 使用using对类型名称进行重定义
    using statusFlag = std::array<bool, MAX_NO_MAIN_MENU_STATUS_FLAGS>;
    statusFlag flagMenu{};
    // 其实上面两行就相当于
    // std::array<bool, 5> flagMenu{};
    /*这样做的好处就是将bool类型数组容器中的每个元素的下标索引 用枚举类型中的枚举常量
    来表示了，因此，数组容器中的每一个元素，都有了实际的意义。*/

    // 单独定义 ： 错误选择标志位
    bool flagInputError{};

    void receiveInputFlags(std::istream &in_os) {
        // 重置错误选择标志 -> 0
        flagInputError = bool{};
        char c;
        in_os >> c;
        switch (c) {
        case '1':
            flagMenu[FLAG_START_GAME] = true;
            break;
        case '2':
            flagMenu[FLAG_CONTINUE_GAME] = true;
            break;
        case '3':
            flagMenu[FLAG_DISPLAY_HIGHSCORES] = true;
            break;
        case '4':
            flagMenu[FLAG_EXIT_GAME] = true;
            break;

        // 如果用户输入错误，则继续循环，直到读取到正确的输入
        default:
            flagInputError = true;
            break;
        }
    }

    void processMainMenu() {
        if(flagMenu[FLAG_START_GAME]) {
            Game::startGame();
        }
        if(flagMenu[FLAG_CONTINUE_GAME]) {
            // TODO:继续之前存档的游戏
            // continueGame();
        }
        if(flagMenu[FLAG_DISPLAY_HIGHSCORES]) {
            // TODO:显示游戏最高分，可能需要游戏过程中后台持续记录游戏的最高分
            // showScores();
        }
        if(flagMenu[FLAG_EXIT_GAME]) {
            exit(EXIT_SUCCESS);
        }
    }


    // 整个系统就是对这个函数进行无限循环
    bool oneLoop() {
        // 首先重置所有标志位 ->0
        flagMenu = statusFlag{};

        cleanScreen();
        
        drawAlways(std::cout, Game::Graphics::asciiArt2048);
        // dataSuppliment是一个模板函数，第二个参数直接提供函数名字即可
        drawAlways(std::cout, 
                   dataSuppliment(flagInputError, 
                                  Game::Graphics::Menu::mainMenuGraphicsOverlay));

        // 读取用户输入并处理
        receiveInputFlags(std::cin);
        processMainMenu();

        // 给顶层调用返回错误标志位
        // 如果用户没有选择错误，就一直循环下去
        return flagInputError;
    }

    void endlessLoop() {
        while(oneLoop()) {
            ;
        }
    }
}


// 游戏启动函数
// 启动游戏选择按钮
namespace Menu{
    void startMenu() {
        endlessLoop();
    }
}