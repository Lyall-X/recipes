#include <cstdlib>
#include <limits>
#include <source_location>
#include <stdexcept>

int MakeException()
{
    throw std::runtime_error("An error occurred");
    printf("This line will not be executed\n");
}

int ThrowNum()
{
    // can throw varity of types
    // must catch the same type
    throw "dada";
}

// noreturn: used in 1.ternimate function 2. infinite loop
[[noreturn]]
void MyTernimateHandle()
{
    printf("MyTernimate\n");
    // not clean resource
    _Exit(EXIT_SUCCESS);
}

void NoExcept() noexcept
{
    int b = 0;
    int a = 10 / b;
    printf("a:%d\n", a);
}

class MyException : public std::exception
{
 public:
    MyException(std::source_location local = std::source_location::current())
    {
        printf("file:%s, line:%d, function:%s\n", local.file_name(), local.line(), local.function_name());
    }
    const char* what() const noexcept override
    {
        return "MyException";
    }
};

void ThrowMyException()
{
    throw MyException();
}

void LogMessage(std::source_location local = std::source_location::current())
{
    printf("file:%s, line:%d, function:%s\n", local.file_name(), local.line(), local.function_name());
}

void NestException()
{
    try
    {
        throw std::runtime_error("An error occurred: runtime_error");
    }
    catch (const std::exception& e)
    {
        printf("error:%s \n", e.what());
        throw_with_nested(
            MyException());
    }
}

// function try block
class TryBlock
{
 public:
    TryBlock()
    try : a{4}
    {
        int arr[] = {1, 2, 3};
        printf("TryBlock:%d\n", arr[a]);
    }
    catch (const std::bad_alloc& e)
    {
        printf("bad_alloc:%s\n", e.what());
    }

 private:
    int a;
};

int main()
{
    std::set_terminate(MyTernimateHandle);
    try
    {
#if 0
        MakeException();
        ThrowNum();
        NoExcept();
        LogMessage();
        ThrowMyException();
        NestException();
#endif
        TryBlock tb;
    }
    catch (const char* e)
    {
        printf("error:%s \n", e);
    }
    catch (const MyException& e)
    {
        printf("My Exception:%s \n", e.what());
        const auto* nested_exp{dynamic_cast<const std::nested_exception*>(&e)};
        if (nested_exp)
        {
            try
            {
                nested_exp->rethrow_nested();
            }
            catch (const std::exception& e)
            {
                printf("nested exeception rethrow:%s\n", e.what());
            }
        }
    }
    catch (const std::exception& e)
    {
        printf("error:%s \n", e.what());
    }
    catch (...)
    {
        printf("error:unknown \n");
    }

    printf("no except:%d\n", noexcept(NoExcept));
}