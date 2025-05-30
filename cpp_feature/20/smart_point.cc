/**
 * @file smart_point.cc
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-10-20
 *  1. 普通指针不会调用派生类的析构函数
 *  2. shared_ptr会调用派生类的析构函数
 * @copyright Copyright (c) 2024
 *
 */
#include <cstdio>
#include <memory>

class Base
{
 public:
    Base()
    {
        printf("Base constructor\n");
    }
    virtual ~Base()
    {
        printf("Base destructor\n");
    }
};
class Derived : public Base
{
 public:
    Derived()
    {
        printf("Derived constructor\n");
    }
    ~Derived() override
    {
        printf("Derived destructor\n");
    }
};

int main()
{
    // 普通指针不掉用派生类的析构函数
    Base* b = new Derived();
    delete b;
    printf("\n");
    Derived* d = new Derived();
    delete d;
    printf("\n");
    std::shared_ptr<Base> b2 = std::make_shared<Derived>();
    return 0;
}