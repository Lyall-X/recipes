#include <cstdio>
#include <map>
#include <ranges>
#include <string>
#include <vector>

using namespace std;

template <typename T>
void P()
{
    printf("%s\n", __PRETTY_FUNCTION__);
}

int main()
{
    map<string, string> m{{"a", "1"}, {"b", "2"}, {"c", "3"}};

    auto r = m | views::values;
    auto c = vector<string>(begin(r), end(r));
    P<decltype(r)>();
    P<decltype(c)>();
    for (auto i : r)
    {
        printf("%s\n", i.c_str());
    }

    return 0;
}