#ifndef __POINT2D_H
#define __POINT2D_H

#include <tuple>

class point2D_t {
    // 游戏面板中每一个方格的坐标(x,y),用tuple表示
    // TODO:这里对关键字重命名,为什么又使用了typename?
    using point_datatype_t = typename std::tuple<int, int>;

    // 数据成员为一个坐标
    point_datatype_t point_vector{};
    explicit point2D_t(const point_datatype_t pt) : point_vector(pt) {}

public:
    enum class pointCoord{COORD_X, COORD_Y};
    // 表明这个类除了上面的带参构造函数之外,还存在默认构造函数
    point2D_t() = default;
    // TODO:默认构造函数可以没有默认参数值吗?
    point2D_t(const int x, const int y) : point2D_t(std::make_tuple(x, y)) {}

    // 获取一个二维坐标点的其中一维
    template<pointCoord dimension>
    int get() const {
        return std::get<static_cast<int>(dimension)>(point_vector);
    }
    // 给其中一维赋值
    template<pointCoord dimension>
    void set(int value) {
        std::get<static_cast<int>(dimension)>(point_vector) = value;
    }
    // 再次重载get函数,返回二维坐标
    point_datatype_t get() const {return point_vector;}
    void set(point_datatype_t value) {point_vector = value;}
    void set(const int x, const int y) {set(std::make_tuple(x, y));}

    // 运算符重载,实现坐标之间的快速运算
    point2D_t &operator+=(const point2D_t &pt) {
        this->point_vector = std::make_tuple(
            get<pointCoord::COORD_X>() + pt.get<pointCoord::COORD_X>(),
            get<pointCoord::COORD_Y>() + pt.get<pointCoord::COORD_Y>()
        );
        return *this;
    }
    point2D_t &operator-=(const point2D_t pt) {
        this->point_vector = std::make_tuple(
            get<pointCoord::COORD_X>() - pt.get<pointCoord::COORD_X>(),
            get<pointCoord::COORD_Y>() - pt.get<pointCoord::COORD_Y>()
        );
        return *this;
    }
};

// TODO:为什么不直接写在类中呢?
inline point2D_t operator+(point2D_t l, point2D_t &r) {
    l += r;
    return l;
}

inline point2D_t operator-(point2D_t l, point2D_t &r) {
    l -= r;
    return l;
}

#endif