/**
 * @file chapter_12.cc
 * @brief
 * @version 0.1
 * @date 2024-09-18
 *  1.std::size_t is better than int/uint32_t
 *  2.copy-and-swap idiom: just for copy assignment operator; move semantic is noexpt func
 *  3.std::strcmp(): compare with char*
 *  4.auto: strip away reference and const qualifiers, but decltype don't strip it. decltype(auto): Before c++14, using auto func() -> decltype(expression)
 * @copyright Copyright ASDA(c) 2024
 *
 */
#include <stdlib.h>

#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

constexpr std::size_t DefaultWidth  = 5;
constexpr std::size_t DefaultHeight = 10;

template <typename T, std::size_t WIDTH = DefaultWidth, std::size_t HEIGHT = DefaultHeight>
class Grid
{
 public:
    // default constructor
    // explicit: avoid implicit conversion when not using defult constructor
    Grid() = default;
    // virtual function can't be a template function
    virtual ~Grid() = default;

    // copy constructor
    template <typename E, std::size_t WIDTH2, std::size_t HEIGHT2>
    Grid(const Grid<E, WIDTH2, HEIGHT2>& src);
    // copy assignment operator
    template <typename E, std::size_t WIDTH2, std::size_t HEIGHT2>
    Grid& operator=(const Grid<E, WIDTH2, HEIGHT2>& rhs)
    {
        // copy-and-swap idiom
        Grid<T, WIDTH, HEIGHT> temp{rhs};
        swap(temp);
        return *this;
    }

    // move constructor
    Grid(Grid&& src) = default;
    // move assignment operator
    Grid& operator=(Grid&& rhs) = default;

 public:
    // c++ 20
    // c++ 23: Self template
    const std::optional<T>& at(std::size_t x, std::size_t y) const
    {
        verifyCoordinate(x, y);
        return m_cells[x][y];
    }
    std::optional<T>& at(std::size_t x, std::size_t y)
    {
        return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
    }

    std::size_t getWidth() { return WIDTH; }
    std::size_t getHeight() { return HEIGHT; }

 private:
    void verifyCoordinate(std::size_t x, std::size_t y) const;
    template <typename E, std::size_t WIDTH2, std::size_t HEIGHT2>
    void swap(Grid<E, WIDTH2, HEIGHT2>& src)
    {
        std::swap(m_cells, src.m_cells);
    }

 private:
    std::optional<T> m_cells[WIDTH][HEIGHT];
};

template <typename T, std::size_t WIDTH, std::size_t HEIGHT>
template <typename E, std::size_t WIDTH2, std::size_t HEIGHT2>
Grid<T, WIDTH, HEIGHT>::Grid(const Grid<E, WIDTH2, HEIGHT2>& src)
{
    for (std::size_t i{0}; i < WIDTH; ++i)
    {
        for (std::size_t j{0}; j < HEIGHT; ++j)
        {
            if (i < WIDTH2 && j < HEIGHT2)
            {
                m_cells[i][j] = src.at(i, j);
            }
            else
            {
                m_cells[i][j].reset();  // optional function
            }
        }
    }
};

template <typename T, std::size_t WIDTH, std::size_t HEIGHT>
void Grid<T, WIDTH, HEIGHT>::verifyCoordinate(std::size_t x, std::size_t y) const
{
    if (x >= WIDTH)
    {
        char buffer[100];
        std::sprintf(buffer, "x (%zu) must be less than width (%zu).", x, WIDTH);
        throw std::out_of_range(buffer);
    }
    if (y >= HEIGHT)
    {
        char buffer[100];
        std::sprintf(buffer, "y (%zu) must be less than height  (%zu).", y, HEIGHT);
        throw std::out_of_range(buffer);
    }
};

// explicit Instantiation: check all member function compile error
template class Grid<int>;

// alias template: using is better than typedef
using GRID = Grid<std::string>;
template <typename T>
using GRID2 = Grid<T, 10, 100>;

int main()
{
    // 1.template parameter can't const type
    /*
        std::size_t hight = 10;
        Grid<int ,10, hight> error_1; //  DOEST NOT COMPILE

        const std::size_t hight = 10;
        Grid<int, 10, hight> g1;
        constexpr std::size_t getHeight() { return 10; }
        Grid<int, 10, getHeight()> g2;
    */

    // 2.CTAD: class template argument deduction: function template helper is no longer necessary

    Grid<int> grid;
    grid.at(1, 2).value_or(0);
    return 0;
}
// std::optional<>
//     value_or
//         T {}

// explicit template
// template class for compile
// CADT
// User Define Deducion
// as_const
// dedcing this
// forward_like

///////////////////////////////////////////////////////////////////////////////////////////////////
// User-Defined Deduction Guides: Only Applicable for constructor func
/*
    template <...>
    explicit(optional) TemplateName(Parameters) -> DeducedTemplate<...>;

    when T=const char*, then deduce to std::string
*/
template <typename T>
class UDDGTest
{
 public:
    UDDGTest(T t) : m_content(std::move(t)) {}

 private:
    T m_content;
};

UDDGTest(const char*) -> UDDGTest<std::string>;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Return Type of Function Templates
// c++ 20 & abbreviated: Best
template <typename T>
decltype(auto) func1(const T& t1, const T& t2)
{
    return t1 + t2;
}
// 1.each auto type different template type
// 2.can't know the template explicit type
decltype(auto) func1_ab(const auto& t1, const auto& t2)
{
    return t1 + t2;
}

// c++ 14: beginning of the prototype line, but these are not yet known
// template <typename T>
// decltype(t1 + t2) func2(T t1, T t2)
// {
//     return t1 + t2;
// }
template <typename T>
auto func2(const T& t1, const T& t2) -> decltype(t1 + t2)
{
    return t1 + t2;
}
//  using std::declval<>(), determined during compilation
template <typename T>
decltype(std::declval<T>() + std::declval<T>()) func3(const T& t1, const T& t2)
{
    return t1 + t2;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// concept