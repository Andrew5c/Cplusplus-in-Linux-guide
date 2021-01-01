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
            // 竖线绘制方框的边界
            constexpr auto vertical_border_pattern = "|";
            // TODO:如何输入下面这种符号?
            constexpr auto top_board = 
                "┌───────────────────────────┐";
            constexpr auto bottom_board =
                "└───────────────────────────┘";
            const auto outer_border_padding = 
                std::string(UI_BORDER_OUTER_PADDING, border_padding_char);
            const auto inner_border_padding = 
                std::string(UI_BORDER_INNER_PADDING, border_padding_char);
            // TODO:下面这个 std::string{inner_border_padding}.length() 的值是不是应该等于 UI_BORDER_INNER_PADDING ?
            // 计分板上除去两边空白区的可用字符长度
            const auto inner_padding_length = 
                UI_SCOREBOARD_SIZE - (std::string{inner_border_padding}.length() * 2);

            enum scoreboardDisplayDataFields {
                IDX_GAMEBOARD_SCORE,
                IDX_BESTSCORE,
                IDX_MOVECOUNT,
                MAX_SCOREBOARDDISPLAY_INDEXES
            };
            const auto gameboard_score = std::get<IDX_GAMEBOARD_SCORE>(scdd);
            const auto best_score = std::get<IDX_BESTSCORE>(scdd);
            const auto movecount = std::get<IDX_MOVECOUNT>(scdd);
            // 计算在计分板中,为了让右端数据对其,需要的空白字符数
            int char_num_gameboard_score = inner_padding_length
                - std::string{score_text_label}.length() - gameboard_score.length();
            int char_num_best_score = inner_padding_length
                - std::string{bestscore_text_label}.length() - best_score.length();
            int char_num_movecount = inner_padding_length
                - std::string{moves_text_label}.length() - movecount.length();
            // 下面根据上面定义的元素进行顺序输出,绘制计分板
            str_os << outer_border_padding << top_board << "\n";
            str_os << outer_border_padding << vertical_border_pattern << inner_border_padding
                   << score_text_label << std::string(char_num_gameboard_score, border_padding_char)
                   << gameboard_score << inner_border_padding << vertical_border_pattern << "\n";

            str_os << outer_border_padding << vertical_border_pattern << inner_border_padding
                   << bestscore_text_label << std::string(char_num_best_score, border_padding_char)
                   << best_score << inner_border_padding << vertical_border_pattern << "\n";

            str_os << outer_border_padding << vertical_border_pattern << inner_border_padding
                   << moves_text_label << std::string(char_num_movecount, border_padding_char)
                   << movecount << inner_border_padding << vertical_border_pattern << "\n";

            str_os << outer_border_padding << bottom_board << "\n \n";
            return str_os.str();
        }

        std::string gameScoreBoardOverlay(scoreboard_display_data_t scdd) {
            std::ostringstream str_os;
            drawAlways(str_os, dataSuppliment(scdd, gameScoreBoardBox));
            return str_os.str();
        }
    } // namespace Graphics
    
} // namespace Game
