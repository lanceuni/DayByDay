#!/bin/bash

# 确保在gtest目录下执行脚本
cd /home/lanceuni/workspace/dayByDay/gtest

# 清除旧的覆盖率数据文件和报告
rm -rf out/

# 重新编译项目以生成新的覆盖率数据文件
# 只对src.cpp应用覆盖率编译选项，避免为main.cpp和src_test.cpp生成覆盖率数据
g++ -std=c++17 -isystem /usr/local/include -pthread -c -fprofile-arcs -ftest-coverage src.cpp 
g++ -std=c++17 -isystem /usr/local/include -pthread -c main.cpp src_test.cpp
# 添加-lgcov选项以链接覆盖率相关的库
g++ -std=c++17 -pthread src.o src_test.o main.o /usr/local/lib/libgtest.a -lgcov -o test
# 运行测试程序
./test

# 直接使用gcov生成覆盖率数据
gcov -b src.cpp

# 生成覆盖率报告
lcov --capture --directory . --output-file coverage.info
# 排除不需要统计覆盖率的文件
lcov --rc lcov_branch_coverage=1 --capture --directory . --output-file coverage.info
lcov --rc lcov_branch_coverage=1 --remove coverage.info '/usr/*' 'main.cpp' -o coverage_filtered.info
genhtml --branch-coverage coverage_filtered.info --output-directory out
# 清理临时文件
rm -rf *.o *.gcov *info test
mv *.gcda *.gcno ./out
echo "覆盖率报告已生成在out目录中"
