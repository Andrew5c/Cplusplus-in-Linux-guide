#ifndef __GAME_H
#define __GAME_H

namespace Game {
    struct gameBoard;
    
    enum class playGameFlag {brandNewGame, continuePreGame};
    
    void playGame(playGameFlag cont, gameBoard gb, 
                  unsigned long long game_board_size = 4);
    
    void startGame();
    void continueGame();
} // namespace Game



#endif