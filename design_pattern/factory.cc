#include <iostream>
// Item
class BaseItem
{
public:
    virtual void Name() = 0;
};

class WeaponItem : public BaseItem
{
public:
    void Name() override
    {
        std::cout << "WeaponItem" << std::endl;
    }
};

class MaterialItem : public BaseItem
{
public:
    void Name() override
    {
        std::cout << "MaterialItem" << std::endl;
    }
};
enum ItemType
{
    Weapon = 0,
    Material = 1
};

// Factory
class ItemFactory
{
public:
    BaseItem *Create( ItemType type = Weapon)
    {
        if (type == Weapon)
        {
            return new WeaponItem();
        }
        else
        {
            return new MaterialItem();
        }
    }
};

int main()
{
    ItemFactory factory;
    BaseItem *item = factory.Create(ItemType::Weapon);
    item->Name();
    return 0;
}