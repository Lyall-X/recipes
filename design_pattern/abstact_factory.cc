#include <iostream>

// 由工厂类别开始推导
enum FactoryType
{
    WeaponFactoryType = 0,
    MaterialFactoryType = 1
};

// 归纳工厂的共性
class BaseItem;
class BaseFactory
{
public:
    virtual BaseItem* CreateItem() = 0;
};

enum ItemType
{
    Weapon = 0,
    Material = 1
};
class BaseItem
{
public:
    virtual void Name() = 0;
};

// 武器工厂制造武器
class WeaponItem : public BaseItem
{
public:
    void Name() override
    {
        std::cout << "WeaponItem" << std::endl;
    }
};

class WeaponFactory : public BaseFactory
{
public:
    BaseItem* CreateItem() override
    {
        return new WeaponItem();
    }
};

// 材料工厂制造材料
class MaterialItem : public BaseItem
{
public:
    void Name() override
    {
        std::cout << "MaterialItem" << std::endl;
    }
};

class MaterialFactory : public BaseFactory
{
public:
    BaseItem* CreateItem() override
    {
        return new MaterialItem();
    }
};

int main()
{
    BaseFactory *weapon_factory = new WeaponFactory();
    BaseItem *weapon = weapon_factory->CreateItem();
    weapon->Name();

    BaseFactory *material_factory = new MaterialFactory();
    BaseItem *material = material_factory->CreateItem();
    material->Name();
    return 0;
}