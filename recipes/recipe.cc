#include <iostream>
#include <map>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

void TestHash()
{
    std::map<int, int> buckets;
    for (int i = 0; i < 100000; ++i)
    {
        // 创建随机数的id
        std::random_device rd;                                // 获取随机数种子
        std::mt19937 gen(rd());                               // 使用 Mersenne Twister 算
        std::uniform_int_distribution<> dis(1, 1000000);      // 生成 1 到 1000000 的随机数
        int user_id     = dis(gen);                           // 生成随机用户 ID
        std::string key = "user:" + std::to_string(user_id);  // 随机生成用户 ID
        std::cout << "key: " << key << std::endl;
        auto h     = std::hash<std::string>{}(key);
        int bucket = h % 16;
        buckets[bucket]++;  // 统计每个 bucket 命中次数
    }
    for (const auto &pair : buckets)
    {
        std::cout << "Bucket " << pair.first << ": " << pair.second << " hits" << std::endl;
    }
}
int main()
{
    TestHash();
    return 0;
}