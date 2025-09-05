#include <algorithm>
#include <atomic>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#define GDEBUG1(param1)                                      \
    do                                                       \
    {                                                        \
        std::cout << #param1 << ": " << param1 << std::endl; \
    } while (0)
#define GDEBUG2(param1, param2)                                                                   \
    do                                                                                            \
    {                                                                                             \
        std::cout << #param1 << ": " << param1 << ", " << #param2 << ": " << param2 << std::endl; \
    } while (0)
#define GDEBUG3(param1, param2, param3)                                                                                                \
    do                                                                                                                                 \
    {                                                                                                                                  \
        std::cout << #param1 << ": " << param1 << ", " << #param2 << ": " << param2 << ", " << #param3 << ": " << param3 << std::endl; \
    } while (0)
#define GDEBUG4(param1, param2, param3, param4)                                                                                                                             \
    do                                                                                                                                                                      \
    {                                                                                                                                                                       \
        std::cout << #param1 << ": " << param1 << ", " << #param2 << ": " << param2 << ", " << #param3 << ": " << param3 << ", " << #param4 << ": " << param4 << std::endl; \
    } while (0)
#define GET_MACRO(_1, _2, _3, _4, NAME, ...) NAME
#define GDEBUG(...) GET_MACRO(__VA_ARGS__, GDEBUG4, GDEBUG3, GDEBUG2, GDEBUG1)(__VA_ARGS__)