#include <iostream>

class Library
{
public:
    void Load()
    {
        std::cout << "Load" << std::endl;
    }

    void Unload()
    {
        std::cout << "Unload" << std::endl;
    }

    void Play()
    {
        std::cout << "Play" << std::endl;
    }
};

// 外观类是对复杂类的封装，提供一个简单的接口
class Facade
{
public:
    void Play()
    {
        library_.Load();
        library_.Play();
        library_.Unload();
    }
private:
    Library library_;
};

int main()
{
    Facade facade;
    facade.Play();
    return 0;
}