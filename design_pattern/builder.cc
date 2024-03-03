#include <iostream>
// 1.产品自己的属性
struct WeaponItem
{
    void Equip()
    {
        std::cout << "equip" << std::endl;
    }
    void Attack()
    {
        std::cout << "attack" << std::endl;
    }
    int32_t attack;
};

// 2.依据产品属性的使用方式
class ItemBuilder
{
public:
    virtual void Default() = 0;
    virtual void Use() = 0;
};

class WeaponUseBuilder : public ItemBuilder
{
public:
    void Default()
    {
        weapon.attack = 10;
    }
    void Use()
    {
        weapon.Equip();
        weapon.Attack();
    }
    WeaponItem weapon;
};

// 3.完整使用流程的梳理
class Director
{
public:
    void Construct(ItemBuilder *builder)
    {
        builder->Default();
        builder->Use();
    }
};

int main()
{
    ItemBuilder* builder = new WeaponUseBuilder();
    Director director;
    director.Construct(builder);
    return 0;
}
