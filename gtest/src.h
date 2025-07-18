#ifndef SRC_H
#define SRC_H

#include <memory>
#include <iostream>

// 函数声明
int Add(int a, int b);

// 资源持有类声明
class ResourceHolder {
public:
    ResourceHolder();
    ~ResourceHolder();
};

// 日志类声明
class Logger {
public:
    static Logger& getInstance();
    
private:
    Logger();  // 私有构造函数
};

// 类A声明 - 基类
class A {
public:
    static A& getInstance();
    
protected:  // 修改访问权限为protected
    A();  // 构造函数
};

// 类B声明 - 继承自A
class B : public A {
public:
    static B& getInstance();
    
    // 禁用拷贝构造
    B(const B&) = delete;
    B& operator=(const B&) = delete;

    class C {
    public:
        int add(int a, int b);
        int addIf(int a, int b);
        int subtract(int a, int b);
        int multiply(int a, int b);
        int divide(int a, int b);
        
    private:
        int test1;
        int test2;
    };
    
private:
    B();  // 私有构造函数
    static B instance;  // 添加静态实例
    std::unique_ptr<C> pImpl;
};

namespace mac{
namespace adas{

class processBase{
public:
    virtual void Start() = 0;
    virtual void Run() = 0;
    virtual void Stop() = 0;
};

class Testprocess : public processBase {
public:
    virtual void Start(){
        std::cout<<"Testprocess Start"<<std::endl;
    }
    virtual void Run(){
        std::cout<<"Testprocess Run"<<std::endl;
    }
    virtual void Stop() {
        std::cout<<"Testprocess Stop"<<std::endl;
    }
    Testprocess* testprocess;
};

};// namespace adas
};// namespace mac
#endif // SRC_H