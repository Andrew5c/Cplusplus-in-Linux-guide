#include "gameboard-graphics.hpp"
#include "gameboard.hpp"
#include "point2d.hpp"
#include "tile-graphics.hpp"

#include <array>
#include <sstream>
#include <algorithm>

namespace Game {
    namespace GameBoard {
        namespace Graphics {
            namespace {
                
                // 绘制游戏面板的模板函数,根据游戏尺寸进行调整
                // 该函数输出了绘制一个面板所需要的核心元素,也就是上边框,中间分隔,下边框
                // 需要多大的面板,对函数的输出数组进行合理的循环排列即可
                // 函数实现了可调面板的横向伸缩
                template<size_t num_of_bars>
                std::array<std::string, num_of_bars> makePatternedBars(int playsize) {
                    // 定义具有num_of_bars个string类型元素的数组,并初始化
                    // 作为返回值暂存容器
                    auto temp_bars = std::array<std::string, num_of_bars>{};
                    using bar_pattern_t = std::tuple<std::string, std::string, std::string>;

                    const auto bar_pattern_list = {std::make_tuple("┌", "┬", "┐"),
                                                   std::make_tuple("├", "┼", "┤"),
                                                   std::make_tuple("└", "┴", "┘")};
                    // 利用匿名函数产生水平方框
                    const auto generate_x_bar_pattern = [playsize](bar_pattern_t t) {
                        enum {PATTERN_HEAD, PATTERN_MID, PATTERN_TAIL};
                        const auto sp = "  ";
                        const auto separator = "──────";
                        std::ostringstream temp_richtext;
                        // 先输出一个开头,然后根据面板尺寸循环输出网格
                        temp_richtext << sp << std::get<PATTERN_HEAD>(t);
                        for(auto i=0; i<playsize; i++) {
                            bool is_not_last_column = (i < (playsize-1));
                            temp_richtext << separator 
                                          << (is_not_last_column ? std::get<PATTERN_MID>(t) : 
                                                                   std::get<PATTERN_TAIL>(t));
                        }
                        temp_richtext << "\n";
                        return temp_richtext.str();
                    };
                    std::transform(std::begin(bar_pattern_list), std::end(bar_pattern_list), 
                                   std::begin(temp_bars), generate_x_bar_pattern);
                    return temp_bars.str();
                }

                // 对上面的元素进一步的整理排列,实现整个面板的大小可调
                std::string drawSelf(gameBoard::gameboard_data_tuple_t gbda) {
                    std::ostringstream str_os;
                    enum {TOP_BAR, XN_BAR, BASE_BAR, MAX_TYPE_OF_BAR};
                    const int playsize = 4;
                    const auto vertical_bar = makePatternedBars<MAX_TYPE_OF_BAR>(playsize);
                    for(auto y=0; y<playsize; y++) {
                        // 绘制主要框架,也就是每个角点和水平线,不包括竖直分隔线
                        bool is_first_row = (y == 0);
                        str_os << (is_first_row ? std::get<TOP_BAR>(vertical_bar) : 
                                                  std::get<XN_BAR>(vertical_bar));
                        for(auto x=0; x<playsize; x++) {
                            // 对于每一行,在上下水平线之间绘制分隔线,注意开头的分隔线和中间分隔线的区别
                            bool is_first_col = (x == 0);
                            const auto sp = (is_first_row ? "  " : " ");
                            // 获取坐标所指示的方格中数据
                            // TODO:这里使用point2D_t类的默认构造函数,为什么用{},而不是()?
                            const auto tile = getTileOnGameboardDataArray(gbda, point2D_t{x, y});
                            str_os << sp << "| " << drawTileString(tile);
                        }
                        // 绘制每一行的结束
                        str_os << " |" << "\n";
                    }
                    str_os << std::get<BASE_BAR>(vertical_bar) << "\n";
                    return str_os.str();
                }
            } // namespace

            std::string gameBoardTextOutput(gameBoard gb) {
                return drawSelf(gb.gbda);
            }
        } // namespace Graphics
    }// namespace Gameboard
}// namespace Game
