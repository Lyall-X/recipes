#include <iostream>

// 1.创建一个已经在用的服务
class Command
{
public:
    void Execute(std::string name)
    {
        std::cout << "Command: " << name << std::endl;
    }
};

class CommandAdapter
{
public:
    CommandAdapter(Command* command) : command_(command) {}
    void Execute(int32_t count, std::string name)
    {
        for (int32_t i = 0; i < count; ++i)
        {
            command_->Execute(name);
        }
    }
private:
    Command* command_;
};

int main()
{
    Command command;
    CommandAdapter adapter(&command);
    adapter.Execute(3, "adapter");
    return 0;
}