#ifndef __GAME_H
#define __GAME_H

namespace Game {
    // 这个结构体被定义在 gameboard.cpp
    // TODO:这里算是对变量的外部声明吗？
    struct gameBoard;
    
    enum class playGameFlag {brandNewGame, continuePreGame};
    
    void playGame(playGameFlag cont, gameBoard gb, 
                  unsigned long long game_board_size = 4);
    
    void startGame();
    void continueGame();
} // namespace Game



#endif