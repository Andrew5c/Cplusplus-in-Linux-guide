#include "game-graphics.hpp"
#include "color.hpp"
#include "global.hpp"
#include <array>
#include <iomanip>
#include <sstream>
/*
1. 绘制游戏启动界面
*/

namespace Game
{
    namespace Graphics
    {
        std::string asciiArt2048() {
            // TODO: this give a good title card
            constexpr auto title_card_2048 = R"(2048)";
            std::ostringstream str_os;
            // TODO: add the color and fonts
            str_os << title_card_2048;
            str_os << "\n\n\n";
            // convert to string class
            return str_os.str();
        }

        std::string gameNoSavePrompt() {
            constexpr auto no_save_text = 
                "No saved game found. Starting a new game...";
            constexpr auto sp = "  ";
            std::ostringstream str_os;
            str_os << sp << no_save_text << "\n\n";
            return str_os.str();
        }
        
        // 绘制计分板
        std::string gameScoreBoardBox(scoreboard_display_data_t scdd) {
            std::ostringstream str_os;
            constexpr auto score_text_label = "SCORE:";
            constexpr auto bestscore_text_label = "BEST SCORE:";
            constexpr auto moves_text_label = "MOVES:";

            enum {
                UI_SCOREBOARD_SIZE = 27,
                UI_BORDER_OUTER_PADDING = 2,
                UI_BORDER_INNER_PADDING = 1
            };
            constexpr auto border_padding_char = ' ';
            constexpr auto vertical_border_pattern = "|";
            constexpr auto top_board = 
                "┌───────────────────────────┐";
            constexpr auto bottom_board =
                "└───────────────────────────┘";
        }

        std::string gameScoreBoardOverlay(scoreboard_display_data_t scdd) {
            std::ostringstream str_os;
            drawAlways(str_os, dataSuppliment(scdd, gameScoreBoardBox));
            return str_os.str();
        }
    } // namespace Graphics
    
} // namespace Game
