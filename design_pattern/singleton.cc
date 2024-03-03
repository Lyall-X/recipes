#include <iostream>

class Singleton
{
public:
    static Singleton GetInstance()
    {
        if (instance_ == nullptr)
        {
            instance_ = new Singleton();
        }
        return *instance_;
    }
    void Print()
    {
        std::cout << "Singleton" << std::endl;
    }
private:
    Singleton() = default;
    static Singleton* instance_;
};

Singleton* Singleton::instance_ = nullptr;

int main()
{
    Singleton::GetInstance().Print();
    return 0;
}