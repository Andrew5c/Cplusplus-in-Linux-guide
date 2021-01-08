#include "gameboard.hpp"
#include "point2d.hpp"
#include "game-graphics.hpp"

#include <algorithm>
#include <tuple>
#include <array>
#include <chrono>
#include <random>
#include <utility>
#include <sstream>

namespace Game
{
    namespace {
        // 产生整数随机数
        class RandInt {
            public:
            using clock = std::chrono::system_clock;
            // 默认构造函数这里一方面给随机分布器确定范围
            // 另一方面使用系统时钟给随机数引擎一个随机种子
            RandInt() : dist{0, std::numeric_limits<int>::max()} {
                seed(clock::now().time_since_epoch().count());
            }
            RandInt(const int low, const int high) : dist{low, high} {
                seed(clock::now().time_since_epoch().count());
            }
            // 仿函数,返回一个产生的随机数
            int operator()() {return dist(re);}
            void seed(const unsigned int s) {re.seed(s);}

            private:
            // 线性同余法随机数产生引擎,可以产生 [1, 2147483646]的随机数
            std::minstd_rand re;
            // 随机数分布器
            // 将均匀分布随机数转化为我们需要的特定分布的随机数
            std::uniform_int_distribution<> dist;
        };

        using gameboard_data_array_t = gameBoard::gameboard_data_tuple_t;
        enum gameboard_data_array_fields {
            IDX_PLAYSIZE,
            IDX_BOARD,
            MAX_NO_INDEXES
        };
        // 数据是无法移动,还是直接转移,还是与目标合并
        enum class COLLAPSE_OR_SHIFT_T {
            ACTION_NONE,
            ACTION_COLLAPSE,
            ACTION_SHIFT,
            MAX_NUM_OF_ACTIONS
        };
        using bool_collapse_shift_t = std::tuple<bool, COLLAPSE_OR_SHIFT_T>;

        // 这个类型中的第一个元素表示当前操作点,第二个元素表示偏移点
        using delta_t = std::pair<point2D_t, point2D_t>;

        // ---------------------------------
        // TODO :C++中,结构体可以和类同样的使用?
        struct gameboard_data_point_t {
            static int point2D_to_1D_index(gameboard_data_array_t gbda, point2D_t pt) {
                int x, y;
                std::tie(x, y) = pt.get();
                return x + getPlaysizeOfGameboardDataArray(gbda)*y;
            }
            // 为结构体重载括号运算符,成为仿函数
            // TODO:下面这两个函数的区别?
            tile_t operator() (gameboard_data_array_t gbda, point2D_t pt) const {
                return std::get<IDX_BOARD>(gbda)[point2D_to_1D_index(gbda, pt)];
            }
            tile_t &operator() (gameboard_data_array_t &gbda, point2D_t pt) {
                return std::get<IDX_BOARD>(gbda)[point2D_to_1D_index(gbda, pt)];
            }
        };
        // 获取或者修改游戏面板中每一个方块的值和属性
        // TODO:这里面为什么这么使用结构体? 
        void setTileOnGameboardDataArray(gameboard_data_array_t &gbda, point2D_t pt, tile_t tile) {
            gameboard_data_point_t{}(gbda, pt) = tile;
        }
        void setTileValueOnGameboardDataArray(gameboard_data_array_t &gbda, point2D_t pt, ull value) {
            gameboard_data_point_t{}(gbda, pt).value = value;
        }
        ull getTileValueOnGameboardDataArray(gameboard_data_array_t gbda, point2D_t pt) {
            return gameboard_data_point_t{}(gbda, pt).value;
        }
        bool getTileBlockedOnGameboardDataArray(gameboard_data_array_t gbda, point2D_t pt) {
            return gameboard_data_point_t{}(gbda, pt).blocked;
        }

        bool if_point_in_board_play_area(point2D_t pt, int playsize) {
            int x, y;
            std::tie(x, y) = pt.get();
            return !(x<0 || x>playsize-1 || y<0 || y>playsize-1);
        }

        // TODO:判断当前游戏面板中是否有方块还可以进行移动
        // 只要游戏面板中有一个方块,其上下左右中存在一个与其数字相同的方块即可,利用 any_of 函数可以方便的实现
        bool canMoveOnGameBoardDataArray(gameboard_data_array_t gbda) {
            // any_of在进行循环检测的时候,本函数中也依次进行索引
            auto index_counter{0};

            // 判断当前方块是否可以移动到他的上下左右任意一个方向
            const auto can_move_to_offset = [=, &index_counter](const tile_t t) {
                const auto current_point_value = t.value;
                const int playsize = getPlaysizeOfGameboardDataArray(gbda);
                const auto current_point = point2D_t{index_counter % playsize, index_counter / playsize};
                index_counter++;
                const auto list_of_offsets = {point2D_t{1, 0}, point2D_t{0, 1}};
                
                const auto offset_in_range_with_same_value = [=](const point2D_t offset) {
                    // 对于offset=(1,0)来说,下面这个check表示检测当前方块的上下
                    // 同样的,offset=(0,1)表示检测左右
                    const auto offset_check = {current_point + offset, 
                                               current_point - offset};
                    for(const auto current_offset : offset_check) {
                        if(if_point_in_board_play_area(current_offset, playsize)) {
                            return getTileValueOnGameboardDataArray(gbda, current_offset) == current_point_value;
                        }
                    }
                    return false;
                };
                return ((current_point_value == 0u) || 
                         std::any_of(std::begin(list_of_offsets), 
                                     std::end(list_of_offsets), offset_in_range_with_same_value));
            };
            return std::any_of(std::begin(std::get<IDX_BOARD>(gbda)), 
                               std::end(std::get<IDX_BOARD>(gbda)), can_move_to_offset);
        }

        // 收集面板中空白的方格索引
        std::vector<size_t> collectFreeTilesOnGameBoardDataArray(gameboard_data_array_t &gbda) {
            std::vector<size_t> freeTiles;
            auto index_count{0};
            // 对保存在vector中的所有方格数据进行区间遍历
            for(const auto t : std::get<IDX_BOARD>(gbda)) {
                if(!t.value) {
                    freeTiles.push_back(index_count);
                }
                index_count++;
            }
            return freeTiles;
        }

        bool addTileOnGameBoardDataArray(gameboard_data_array_t &gbda) {
            // TODO:这个百分比是什么?
            // 新生成的随机数中(只能是2或者4),是4的概率
            constexpr auto CHANCE_OF_VALUE_FOUR_OVER_TWO = 89;
            const auto index_list_of_free_tiles = collectFreeTilesOnGameBoardDataArray(gbda);
            // 如果面板中没有闲置方格,游戏结束
            if(!index_list_of_free_tiles.size()) {
                return true;
            }
            const int playsize = getPlaysizeOfGameboardDataArray(gbda);
            // 随机选择一个闲置方格
            const int rand_selected_index = index_list_of_free_tiles.at(
                RandInt{}() % index_list_of_free_tiles.size()
            );
            // 计算这个方格的二维坐标
            const auto rand_index_as_point_t = point2D_t{
                rand_selected_index % playsize, rand_selected_index / playsize
            };
            const auto value_four_or_two = RandInt{}() % 100 > CHANCE_OF_VALUE_FOUR_OVER_TWO ? 4 : 2;
            setTileValueOnGameboardDataArray(gbda, rand_index_as_point_t, value_four_or_two);
            return false;
        }

        void registerMoveByOneOnGameBoard(gameBoard &gb) {
            gb.moveCount++;
            gb.moved = false;
        }

        // 解锁游戏面板中的小方格
        gameboard_data_array_t 
        unblockTilesOnGameBoardDataArray(gameboard_data_array_t gbda) {
            using tile_data_array_t = gameBoard::tile_data_array_t;
            
            // 初始化一个新的vector，空间是当前游戏面板中的所有小方格数量
            // TODO：但是这句语法是什么？
            auto new_board_data_array = tile_data_array_t(std::get<IDX_BOARD>(gbda).size());
            // 对形参中的数据进行转换
            std::transform(std::begin(std::get<IDX_BOARD>(gbda)), 
                            std::begin(std::get<IDX_BOARD>(gbda)), 
                            std::begin(new_board_data_array), 
                            [](const tile_t t){
                                return tile_t{t.value, false};
                            });
            return gameboard_data_array_t{std::get<IDX_PLAYSIZE>(gbda), 
                                          new_board_data_array};
        }

        bool collapseTilesOnGameboardDataArray(gameboard_data_array_t &gbda, delta_t dt_point) {
            tile_t current_tile = getTileOnGameboardDataArray(gbda, dt_point.first);
            tile_t target_tile = getTileOnGameboardDataArray(gbda, dt_point.first + dt_point.second);
            // 修改进行折叠的两个方块
            current_tile.value = 0;
            target_tile.value *= 2;
            target_tile.blocked = true; 

            setTileOnGameboardDataArray(gbda, dt_point.first, current_tile);
            setTileOnGameboardDataArray(gbda, dt_point.first + dt_point.second, target_tile);

            return true;
        }

        bool shiftTilesOnGameboardDataArray(gameboard_data_array_t &gbda, delta_t dt_point) {
            tile_t current_tile = getTileOnGameboardDataArray(gbda, dt_point.first);
            tile_t target_tile = getTileOnGameboardDataArray(gbda, dt_point.first + dt_point.second);
            // 修改进行折叠的两个方块
            target_tile.value = current_tile.value;
            current_tile.value = 0; 

            setTileOnGameboardDataArray(gbda, dt_point.first, current_tile);
            setTileOnGameboardDataArray(gbda, dt_point.first + dt_point.second, target_tile);

            return true;
        }


        // 判断加上偏移量之后,判断当前数据是转移到目标位置还是和目标位置合并
        bool_collapse_shift_t 
        collapsed_or_shifted_tilesOnGameboardDataArray(gameboard_data_array_t gbda, delta_t dt_point) {
            const auto current_tile = getTileOnGameboardDataArray(gbda, dt_point.first);
            const auto target_tile = getTileOnGameboardDataArray(gbda, dt_point.first+dt_point.second);

            // 对游戏面板中当前方块和目标方块进行逻辑分析,判断是折叠还是移动
            const auto does_value_exist_in_target_point = target_tile.value;
            const auto is_value_same_as_target_value = (current_tile.value == target_tile.value);
            const auto no_tiles_are_blocked = (!current_tile.blocked && !target_tile.blocked);
            // 目标值存在,且和当前数据相同,并且大家都没有被锁定时,可以进行合并
            const auto do_collapse = (does_value_exist_in_target_point && is_value_same_as_target_value && no_tiles_are_blocked);

            const auto is_there_a_current_value_but_no_target_value = (current_tile.value && !target_tile.value);
            const auto do_shift = is_there_a_current_value_but_no_target_value;
            
            const auto action_taken = (do_collapse || do_shift);
            if(do_collapse) {
                return std::make_tuple(action_taken, COLLAPSE_OR_SHIFT_T::ACTION_COLLAPSE);
            }else if(do_shift) {
                return std::make_tuple(action_taken, COLLAPSE_OR_SHIFT_T::ACTION_SHIFT);
            }
            return std::make_tuple(action_taken, COLLAPSE_OR_SHIFT_T::ACTION_NONE);
        }

        bool updateGameboardStatus(gameBoard &gb, ull target_tile_value) {
            gb.score += target_tile_value;
            return true;

            // TODO:源代码中这里会搜索整个游戏面板中最大的数字,如果达到2048,视为游戏胜利
            // 这里暂且不加,仅仅实现常规模式
        }

        // TODO:这个函数的作用?
        bool checkRecursiveOffsetInGameBounds(delta_t dt_point, int playsize) {
            int x, y, x2, y2;
            std::tie(x, y) = dt_point.first.get();
            std::tie(x2, y2) = dt_point.second.get();

            const auto positive_direction = (y2 + x2 == 1);
            const auto negative_direction = (y2 + x2 == -1);
            const auto is_positive_y_direction_flagged = (y2 == 1);
            const auto is_negative_y_direction_flagged = (y2 == -1);

            const auto is_inside_outer_bounds = 
                (positive_direction && (is_positive_y_direction_flagged ? y : x) < playsize-2);
            const auto is_inside_inner_bounds = 
                (negative_direction && (is_negative_y_direction_flagged ? y : x) > 1);

            return (is_inside_inner_bounds || is_inside_outer_bounds);
        }


        // TODO:重要函数,在面板上对小方块进行移动,数据合并
        void moveOnGameboard(gameBoard &gb, delta_t dt_point) {
            auto did_gameboard_collapse_or_shift_anything = bool{};
            auto action_was_taken = COLLAPSE_OR_SHIFT_T::ACTION_NONE;
            // TODO:为什么接收元组中的元素顺序 和 函数反馈的元组中的元素顺序不一致?
            std::tie(did_gameboard_collapse_or_shift_anything, action_was_taken) = 
                collapsed_or_shifted_tilesOnGameboardDataArray(gb.gbda, dt_point);
            if(did_gameboard_collapse_or_shift_anything) {
                gb.moved = true;
                if(action_was_taken == COLLAPSE_OR_SHIFT_T::ACTION_COLLAPSE) {
                    collapseTilesOnGameboardDataArray(gb.gbda, dt_point);
                    const auto target_tile = getTileOnGameboardDataArray(gb.gbda, dt_point.first + dt_point.second);
                    updateGameboardStatus(gb, target_tile.value);
                }
                if(action_was_taken == COLLAPSE_OR_SHIFT_T::ACTION_SHIFT) {
                    shiftTilesOnGameboardDataArray(gb.gbda, dt_point);
                }
            }
            if (checkRecursiveOffsetInGameBounds(dt_point, getPlaysizeOfGameboardDataArray(gb.gbda))) {
                // 递归调用
                moveOnGameboard(gb, std::make_pair(dt_point.first + dt_point.second, dt_point.second));
            }
        }

        void doTumbleTilesUpOnGameboard(gameBoard &gb) {
            const int playsize = getPlaysizeOfGameboardDataArray(gb.gbda);
            for(auto x=0; x<playsize; x++) {
                auto y = 1;
                while(y < playsize) {
                    const auto current_point = point2D_t{x, y};
                    if(getTileValueOnGameboardDataArray(gb.gbda, current_point)) {
                        moveOnGameboard(gb, std::make_pair(current_point, point2D_t{0, -1}));
                    }
                    y++;
                }
            }
        }

        void doTumbleTilesDownOnGameboard(gameBoard &gb) {
            const int playsize = getPlaysizeOfGameboardDataArray(gb.gbda);
            for(auto x=0; x<playsize; x++) {
                // TODO:这里为什么初始位置是-2 ?
                auto y = playsize - 2;
                while(y >= 0) {
                    const auto current_point = point2D_t{x, y};
                    if(getTileValueOnGameboardDataArray(gb.gbda, current_point)) {
                        moveOnGameboard(gb, std::make_pair(current_point, point2D_t{0, 1}));
                    }
                    y--;
                }
            }
        }

        void doTumbleTilesLeftOnGameboard(gameBoard &gb) {
            const int playsize = getPlaysizeOfGameboardDataArray(gb.gbda);
            for(auto y=0; y<playsize; y++) {
                auto x = 1;
                while(x < playsize) {
                    const auto current_point = point2D_t{x, y};
                    if(getTileValueOnGameboardDataArray(gb.gbda, current_point)) {
                        moveOnGameboard(gb, std::make_pair(current_point, point2D_t{-1, 0}));
                    }
                    x++;
                }
            }
        }

        void doTumbleTilesRightOnGameboard(gameBoard &gb) {
            const int playsize = getPlaysizeOfGameboardDataArray(gb.gbda);
            for(auto y=0; y<playsize; y++) {
                auto x = playsize - 2;
                while(x >= 0) {
                    const auto current_point = point2D_t{x, y};
                    if(getTileValueOnGameboardDataArray(gb.gbda, current_point)) {
                        moveOnGameboard(gb, std::make_pair(current_point, point2D_t{1, 0}));
                    }
                    x--;
                }
            }
        }
        
    } // namespace
    
    // 定义hpp文件中的两个构造函数
    gameBoard::gameBoard(ull playsize) : 
        gameBoard{playsize, tile_data_array_t(playsize * playsize)} {}

    gameBoard::gameBoard(ull playsize, tile_data_array_t prempt_board) : 
        gbda{playsize, prempt_board} {}



    size_t getPlaysizeOfGameboardDataArray(gameboard_data_array_t gbda) {
        return std::get<IDX_PLAYSIZE>(gbda);
    }
    // TODO:对上述函数进行重新封装，目的？
    // --------------------------------------------
    
    tile_t getTileOnGameboardDataArray(gameboard_data_array_t gbda, point2D_t pt) {
        return gameboard_data_point_t{}(gbda, pt);
    }

    bool addTileOnGameBoard(gameBoard &gb) {
        return addTileOnGameBoardDataArray(gb.gbda);
    }

    long long moveCountOnGameBoard(gameBoard gb) {
        return gb.moveCount;
    }

    bool canMoveOnGameBoard(gameBoard &gb) {
        return canMoveOnGameBoardDataArray(gb.gbda);
    }

    void registerMoveByOneOnGameboard(gameBoard &gb) {
        gb.moveCount++;
        gb.moved = true;
    }

    void unblockTilesOnGameBoard(gameBoard &gb) {
        gb.gbda = unblockTilesOnGameBoardDataArray(gb.gbda);
    }

    void tumbleTilesUpOnGameboard(gameBoard &gb) {
        doTumbleTilesUpOnGameboard(gb);
    }

    void tumbleTilesDownOnGameboard(gameBoard &gb) {
        doTumbleTilesDownOnGameboard(gb);
    }

    void tumbleTilesLeftOnGameboard(gameBoard &gb) {
        doTumbleTilesLeftOnGameboard(gb);
    }

    void tumbleTilesRightOnGameboard(gameBoard &gb) {
        doTumbleTilesRightOnGameboard(gb);
    }
} // namespace Game
