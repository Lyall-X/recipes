#include <iostream>
#include <string>
#include <unordered_map>

class Flyweight
{
public:
    virtual void GetItem(std::string type) = 0;
};

class WeaponFlyweight : public Flyweight
{
public:
    WeaponFlyweight()
    {
        weapon_["AK47"] = "AK47";
        weapon_["M4A1"] = "M4A1";
    }

    void GetItem(std::string type) override
    {
        if (weapon_.find(type) == weapon_.end())
        {
            weapon_[type] = type;
            std::cout << "新增 Weapon: " << weapon_[type] << std::endl;
        }
        else
        {
            std::cout << "获取 Weapon: " << weapon_[type] << std::endl;
        }
    }
private:
    std::unordered_map<std::string, std::string> weapon_;
};

int main()
{
    Flyweight *flyweight = new WeaponFlyweight();
    flyweight->GetItem("AK47");
    flyweight->GetItem("M4A1");
    flyweight->GetItem("M416");
    return 0;
}