#include <gtest/gtest.h>

// 主函数，用于运行所有测试用例
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}