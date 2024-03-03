#include <iostream>
// 创建抽象部分最基本的功能
class ItemInfo
{
public:
    int32_t GetCount() { return count_; }
    void SetCount(int32_t count) { count_ = count; }
private:
    int32_t count_ = 10;
};

class ItemColor
{
public:
    int32_t GetColor() { return color_; }
    void SetColor(int32_t color) { color_ = color; }
private:
    int32_t color_ = 1;
};

// 创建实现部分，完成复杂的功能
// 组合优于继承
class ItemBridge
{
public:
    void Show()
    {
        if (info_.GetCount() > 0)
        {
            std::cout << "count: " << info_.GetCount() << std::endl;
        }
        if (color_.GetColor() > 0)
        {
            std::cout << "color: " << color_.GetColor() << std::endl;
        }
    }

private:
    ItemInfo info_;
    ItemColor color_;
};

int main()
{
    ItemBridge bridge;
    bridge.Show();
    return 0;
}