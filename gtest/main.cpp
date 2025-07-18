#include <gtest/gtest.h>
#include <iostream>  // 添加头文件用于日志输出

// 全局测试环境类
class GlobalEnvironment : public testing::Environment {
public:
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

// 主函数，用于运行所有测试用例
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    // 注册全局环境类
    testing::AddGlobalTestEnvironment(new GlobalEnvironment());
    
    return RUN_ALL_TESTS();
}