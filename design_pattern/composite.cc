#include <iostream>
#include <vector>

class BaseComponent
{
public:
    virtual void Operation() = 0;
};

class BagComponent : public BaseComponent
{
public:
    void Operation() override
    {
        std::cout << "BagComponent" << std::endl;
    }
};
class WeaponComponent : public BaseComponent
{
public:
    void Operation() override
    {
        std::cout << "WeaponComponent" << std::endl;
    }
};

// 组合的整体
class User
{
public:
    void Add(BaseComponent* component)
    {
        components_.push_back(component);
    }
    void Operation()
    {
        for (auto component : components_)
        {
            component->Operation();
        }
    }
private:
    std::vector<BaseComponent*> components_;
};

int main()
{
    User user;
    user.Add(new BagComponent());
    user.Add(new WeaponComponent());
    user.Operation();
    return 0;
}