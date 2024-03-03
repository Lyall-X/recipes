#include <iostream>

class BaseFD
{
public:
    virtual std::string Read() = 0;
    virtual void Write(std::string data) = 0;
};

class FileFD : public BaseFD
{
public:
    std::string Read() override
    {
        return file_name;
    }
    void Write(std::string data) override
    {
        file_name += data;
    }
private:
    std::string file_name;
};

// 装饰器，需要和被装饰对象拥有同一个基类
class BaseFDDecorator : public BaseFD
{
public:
    virtual void Name() = 0;
};

class EncryptFD : public BaseFDDecorator
{
public:
    EncryptFD(BaseFD *fd) : fd_(fd) {}
    std::string Read() override
    {
        return fd_->Read();
    }
    void Write(std::string data) override
    {
        fd_->Write("加密:" + data);
    }
    void Name() override
    {
        std::cout << "EncryptFD" << std::endl;
    }
private:
    BaseFD *fd_;
};

class CompressFD : public BaseFDDecorator
{
public:
    CompressFD(BaseFD *fd) : fd_(fd) {}
    std::string Read() override
    {
        return fd_->Read();
    }
    void Write(std::string data) override
    {
        fd_->Write("压缩:" + data);
    }
    void Name() override
    {
        std::cout << "CompressFD" << std::endl;
    }
private:
    BaseFD *fd_;
};

int main()
{
    FileFD *file = new FileFD();
    file->Write("A");
    BaseFDDecorator *encrypt = new EncryptFD(file);
    encrypt->Write("B");
    BaseFDDecorator *encrypt2 = new EncryptFD(encrypt);
    encrypt2->Write("C");
    BaseFDDecorator *encrypt3 = new EncryptFD(encrypt2);
    encrypt3->Write("D");
    std::cout << encrypt3->Read() << std::endl;
    return 0;
}