#include "color.hpp"
#include "gameboard.hpp"
#include "tile-graphics.hpp"

#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>


namespace Game {
    // TODO:实现方块中字体颜色随数值大小的变化
    // namespace {
    // } // namespace

    std::string drawTileString(tile_t currentTile) {
        std::ostringstream tile_richtext;
        // 当方块中的数据为0时,不显示,使用空格占位
        if(!currentTile.value) {
            tile_richtext << "    ";
        }else {
            tile_richtext << std::setw(4) << currentTile.value;
        }
        return tile_richtext.str();
    }
    
} // namespace