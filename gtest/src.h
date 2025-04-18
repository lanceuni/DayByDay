#ifndef SRC_H
#define SRC_H

#include <memory>

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
    
private:
    A();  // 私有构造函数
};

// 类B声明 - 继承自A
class B : public A {
public:
    static B& getInstance();
    
    // B的嵌套实现类C
    class C {
    public:
        int add(int a, int b);
        int subtract(int a, int b);
        int multiply(int a, int b);
        int divide(int a, int b);
        
    private:
        int test1;
        int test2;
    };
    
private:
    B();  // 私有构造函数
    std::unique_ptr<C> pImpl;
};

#endif // SRC_H