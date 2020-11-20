#include"menu.hpp"
#include<iostream>



namespace {
    enum mainMenuStatusFlag {
        FLAG_NULL,
        FLAG_START_GAME,
        FLAG_CONTINUE_GAME
    };


    
    bool oneLoop() {
        // 首先重置所有标志位

        cleanScreen();


        // 读取用户输入并处理
        receiveInputFlags(std::cin);
        processMainMenu();
        return
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