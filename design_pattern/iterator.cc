#include <iostream>

// 迭代器基类
template <typename T>
class BaseIterator
{
public:
    virtual T* Next() = 0;
    virtual bool HasMore() = 0;
};

// 具体的迭代器
template <typename T>
class MonsterIterator : public BaseIterator<T>
{
public:
    MonsterIterator(T *monsters, int size)
        : monsters_(monsters), size_(size), index_(0)
    {
    }

    T* Next() override
    {
        if (index_ < size_)
        {
            return &monsters_[index_++];
        }
        return nullptr;
    }

    bool HasMore() override
    {
        return index_ < size_;
    }
private:
    T *monsters_;
    int size_;
    int index_;
};

// 定义迭代器的使用类
class Monster
{
public:
    Monster(const std::string &name, int hp, int mp)
        : name_(name), hp_(hp), mp_(mp)
    {
    }

    void Show()
    {
        std::cout << "Name: " << name_ << " HP: " << hp_ << " MP: " << mp_ << std::endl;
    }
private:
    std::string name_;
    int hp_;
    int mp_;
};

class MonsterGroup
{
public:
    MonsterGroup(Monster *monsters, int size)
        : monsters_(monsters), size_(size)
    {
    }

    void Show()
    {
        MonsterIterator<Monster> iterator(monsters_, size_);
        for (Monster *monster = iterator.Next(); monster != nullptr; monster = iterator.Next())
        {
            monster->Show();
        }
    }
private:
    Monster *monsters_;
    int size_;
};

int main()
{
    Monster monsters[] = {
        Monster("A", 100, 50),
        Monster("B", 200, 100),
        Monster("C", 300, 150),
    };
    MonsterGroup group(monsters, 3);
    group.Show();
    return 0;
}
