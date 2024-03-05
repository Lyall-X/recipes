#include <iostream>
#include <vector>

// 基类定义 责任链 的执行函数
class ComponentWithContextualHelp
{
public:
    virtual bool ClickButton() = 0;
};

// 所有组件的基类
class Container;
class BaseComponent : public ComponentWithContextualHelp
{
public:
    bool ClickButton() override
    {
        if (!help_text_.empty())
        {
            std::cout << help_text_ << std::endl;
            return true;
        }
        return false;
    }
protected:
    std::string help_text_;
};

// 定义组件容器
class Container : public BaseComponent
{
public:
    void Add(BaseComponent *component)
    {
        components_.push_back(component);
    }

    bool ClickButton() override
    {
        if (!help_text_.empty())
        {
            std::cout << help_text_ << std::endl;
            return true;
        }
        for (auto component : components_)
        {
            if (component->ClickButton())
            {
                return true;
            }
        }
        return false;
    }
private:
    std::vector<BaseComponent *> components_;
};

class Button : public BaseComponent
{
public:
    Button(std::string help_text = "")
    {
        help_text_ = help_text;
    }
};
class Panel : public Container
{
public:
    Panel(std::string help_text = "")
    {
        help_text_ = help_text;
    }
};

int main()
{
    Panel panel;
    panel.Add(new Button("Button1"));
    panel.Add(new Button("Button2"));
    panel.Add(new Button("Button3"));
    panel.ClickButton();
    return 0;
}