#include <iostream>

// 定义流程的整体步骤
class GameAI
{
public:
    void playGame()
    {
        initialize();
        startGame();
        endGame();
    }

    virtual void initialize() = 0;
    virtual void startGame() = 0;
    void endGame()
    {
        std::cout << "Game over!" << std::endl;
    }
};

// 子类根据模板，实现自己专有的实现
class MonsterAI : public GameAI
{
public:
    void initialize() override
    {
        std::cout << "MonsterAI initialize" << std::endl;
    }

    void startGame() override
    {
        std::cout << "MonsterAI startGame" << std::endl;
    }
};

int main()
{
    MonsterAI monster;
    monster.playGame();
    return 0;
}