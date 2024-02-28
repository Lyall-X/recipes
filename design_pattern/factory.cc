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

// Factory
class BaseFactory
{
public:
    virtual BaseItem *Create() = 0;
};

class WeaponFactory : public BaseFactory
{
public:
    BaseItem *Create() override
    {
        return new WeaponItem();
    }
};

int main()
{
    BaseFactory *factory = new WeaponFactory();
    BaseItem *item = factory->Create();
    item->Name();
    return 0;
}