#include "gameboard.hpp"
#include "point2d.hpp"

#include <algorithm>
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
        enum gameboard_data_array_fields {IDX_PLAYSIZE,
                                          IDX_BOARD,
                                          MAX_NO_INDEXES};
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


        // 判断当前游戏面板中是否还可以进行移动
        bool canMoveOnGameBoardDataArray(gameboard_data_array_t gbda) {

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
            const auto rand_index_as_point_t = point2D_t{
                rand_selected_index % playsize, rand_selected_index / playsize
            };
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

        
    } // namespace
    
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

    void unblockTilesOnGameBoard(gameBoard &gb) {
        gb.gbda = unblockTilesOnGameBoardDataArray(gb.gbda);
    }
} // namespace Game
