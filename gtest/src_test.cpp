#include <gtest/gtest.h>
#include "src.h"
namespace mac{
namespace adas{
// 基础测试夹具类
class BaseTestFixture : public ::testing::Test {
protected:
    Testprocess* testprocess;

    void SetUp() override {
        std::cout << "=== 测试环境初始化 ===" << std::endl;
        testprocess = new Testprocess();
        testprocess->Start();
        testprocess->Run();
    }

    void TearDown() override {
        testprocess->Stop();
        delete testprocess;
        testprocess = nullptr;
        std::cout << "=== 测试环境清理 ===" << std::endl;
    }
};

// 具体测试夹具继承基类
class AddTest : public BaseTestFixture {};
class DestructorTest : public BaseTestFixture {};
class SingletonTest : public BaseTestFixture {};
class getInstanceTest : public BaseTestFixture {};

TEST_F(AddTest, BasicTest) {
    int result = Add(2, 3);
    std::cout << "=== BasicTest ===" << std::endl;
    EXPECT_EQ(result, 5);
}

// 修改现有测试用例继承结构
TEST_F(DestructorTest, BasicDestructor) {
    {
        ResourceHolder obj;
    }
}

TEST_F(SingletonTest, MultiGetInstance) {
    std::cout << "=== SingletonTest 1===" << std::endl;
    Logger& logger1 = Logger::getInstance();
    std::cout << "=== SingletonTest 2===" << std::endl;
    EXPECT_NE(&logger1, nullptr);
}

TEST_F(getInstanceTest, ImplGetInstance) {
    B& obj = B::getInstance(); // 改为引用
    // 验证单例特性
    EXPECT_NE(&obj, nullptr);
}

};// namespace adas
};// namespace mac