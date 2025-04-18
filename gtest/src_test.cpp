#include <gtest/gtest.h>
#include "src.h"

// 测试用例
TEST(AddTest, BasicTest) {
    int result = Add(2, 3);
    // 断言结果是否符合预期
    EXPECT_EQ(result, 5);
}

// 析构函数测试用例
TEST(DestructorTest, BasicDestructor) {
    {
        ResourceHolder obj;  // 创建对象
        // 对象离开作用域时会自动调用析构函数
    }
}

// 单例测试用例
TEST(SingletonTest, MultiGetInstance) {
    // 第一次调用触发初始化
    Logger& logger1 = Logger::getInstance();
    // 验证单例特性
    EXPECT_NE(&logger1, nullptr); 
}

TEST(getInstanceTest, ImplGetInstance) {
    B obj = B::getInstance();
    // 验证单例特性
    EXPECT_NE(&obj, nullptr);

}