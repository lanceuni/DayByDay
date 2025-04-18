#include "src.h"

// 被测试的函数实现
int Add(int a, int b) {
    return a + b;
}

// ResourceHolder类实现
ResourceHolder::ResourceHolder() {
    // 构造函数实现
}

ResourceHolder::~ResourceHolder() {
    // 析构函数实现
}

// Logger类实现
Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() {
    // 私有构造函数实现
}

// A类实现
A& A::getInstance() {
    static A instance;
    return instance;
}

A::A() {
    // 私有构造函数实现
}

// B类实现
B& B::getInstance() {
    static B instance;
    return instance;
}

B::B() : pImpl(std::make_unique<C>()) {
    // 私有构造函数实现，初始化列表中包含C类的unique_ptr
}

// B::C类实现
int B::C::add(int a, int b) {
    return a + b;
}

int B::C::subtract(int a, int b) {
    return a - b;
}

int B::C::multiply(int a, int b) {
    return a * b;
}

int B::C::divide(int a, int b) {
    return a / b;
}