#include <iostream>
#include <stack>

// 定义命令对象的基类
class BaseApplication;
class BaseCommand
{
public:
    virtual void Execute(BaseApplication *app) = 0;

private:
    std::stack<BaseCommand *> history_;
};

// 调用命令的执行类
class BaseApplication
{
public:
    void Name()
    {
        std::cout << "BaseApplication" << std::endl;
    }
};

// 具体的命令
class PasteCommand : public BaseCommand
{
public:
    void Execute(BaseApplication *app) override
    {
        app->Name();
        std::cout << "Paste" << std::endl;
    }
};

class CopyCommand : public BaseCommand
{
public:
    void Execute(BaseApplication *app) override
    {
        app->Name();
        std::cout << "Copy" << std::endl;
    }
};

// 保存命令的历史记录
class CommandHistory
{
public:
    void Push(BaseCommand *command)
    {
        history_.push(command);
    }
    
    BaseCommand* Pop()
    {
        BaseCommand *command = history_.top();
        history_.pop();
        return command;
    }

private:
    std::stack<BaseCommand *> history_;
};

class Application : public BaseApplication
{
public:
    void Undo()
    {
        BaseCommand *pop_command = history_.Pop();
        pop_command->Execute(this);
    }
    void SendCommand(BaseCommand *command)
    {
        command->Execute(this);
        history_.Push(command);
    }

private:
    CommandHistory history_;
};

int main()
{
    Application app;
    PasteCommand paste;
    CopyCommand copy;
    app.SendCommand(&paste);
    app.SendCommand(&copy);
    app.Undo();
    return 0;
}