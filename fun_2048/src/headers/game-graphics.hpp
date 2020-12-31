#ifndef __GAME_GRAPHICS
#define __GAME_GRAPHICS

#include <string>
#include <tuple>

namespace Game
{
    namespace Graphics
    {
        std::string asciiArt2048();
        std::string gameNoSavePrompt();

        
        // 下面对数据重新打包，方便使用
        // 计分板数据（之前分数，当前最高分数，移动总次数）
        using scoreboard_display_data_t = 
            std::tuple<std::string, std::string, std::string>;

        std::string gameScoreBoardOverlay(scoreboard_display_data_t scdd);
    } // namespace Graphics
    
} // namespace Game

#endif