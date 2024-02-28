#include <iostream>
class BaseItem
{
public:
    virtual void Name() = 0;
};
// 武器
class WeaponItem : public BaseItem
{
public:
    void Name() override
    {
        std::cout << "WeaponItem" << std::endl;
    }
};
// 材料
class MaterialItem : public BaseItem
{
public:
    void Name() override
    {
        std::cout << "MaterialItem" << std::endl;
    }
};

class BaseFactory
{
public:
    virtual BaseItem *CreateItem() = 0;
    virtual BaseItem *CreateMaterial() = 0;
};

class WeaponFactory : public BaseFactory
{
public:
    BaseItem *CreateWeapon() override
    {
        return new WeaponItem();
    }
    BaseItem *CreateMaterial() override
    {
        return new MaterialItem();
    }
};


int main()
{
    return 0;
}