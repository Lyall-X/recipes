#include <iostream>

// 定义访问对象基类
class VisitorBase
{
public:
    virtual void VisitMonsterSpawner(class MonsterSpawner *spawner) = 0;
    virtual void VisitNpcSpawner(class NpcSpawner *spawner) = 0;
};


// 定义被访问对象的基类
class SpawnerBase
{
public:
    virtual void Accept(class VisitorBase *visitor) = 0;
};

// 特殊的被访问对象
class MonsterSpawner : public SpawnerBase
{
public:
    void Accept(class VisitorBase *visitor) override
    {
        visitor->VisitMonsterSpawner(this);
    }
};

class NpcSpawner : public SpawnerBase
{
public:
    void Accept(class VisitorBase *visitor) override
    {
        visitor->VisitNpcSpawner(this);
    }
};

// 具体的访问对象，无关的逻辑可以放在Visitor中实现
class StaticSpawnerVisitor : public VisitorBase
{
public:
    void VisitMonsterSpawner(class MonsterSpawner *spawner) override
    {
        std::cout << "Visit MonsterSpawner" << std::endl;
    }

    void VisitNpcSpawner(class NpcSpawner *spawner) override
    {
        std::cout << "Visit NpcSpawner" << std::endl;
    }
};

class DynamicSpawnerVisitor : public VisitorBase
{
public:
    void VisitMonsterSpawner(class MonsterSpawner *spawner) override
    {
        std::cout << "Dynamic Visit MonsterSpawner" << std::endl;
    }

    void VisitNpcSpawner(class NpcSpawner *spawner) override
    {
        std::cout << "Dynamic Visit NpcSpawner" << std::endl;
    }
};