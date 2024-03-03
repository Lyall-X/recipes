#include <iostream>

// 1.提供Clone函数
class BagCell
{
public:
    virtual BagCell* Clone() = 0;
    virtual void Count() = 0;
};

// 2.实现Clone函数
// 克隆方法会创建一个新对象并将其传递给构造函数
class WeaponCell : public BagCell
{
public:
    WeaponCell() = default;
    WeaponCell(int32_t count) : count_(count) {}
    WeaponCell(const WeaponCell& cell) : count_(cell.count_) {}

    BagCell* Clone() override
    {
        return new WeaponCell(*this);
    }
    void Count() override
    {
        std::cout << "WeaponCell: " << count_ << std::endl;
    }
private:
    int32_t count_;
};

int main()
{
    BagCell* cell = new WeaponCell(100);
    BagCell* new_cell = cell->Clone();
    new_cell->Count();
    return 0;
}