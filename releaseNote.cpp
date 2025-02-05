#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <fstream>

int pro1(int num)
{
    int count_limit = num;
    std::string line;
    int count = 1;

    // 正则表达式用于匹配 ccnc-XXXX 或 ccnc-XXX
    std::regex ccnc_regex(R"(ccnc-(\d{3,4})(?:\|(ccnc-\d{3,4}))*)");
    std::smatch match;

    // 创建输出文件
    std::ofstream output_file("/media/lxy/work/ccncResource/pcsh/releaseNoteAuto/releaseNote.txt");
    if (!output_file) {
        std::cerr << "无法打开文件 releaseNote.txt" << std::endl;
        return 1;
    }

    // 写入中文说明
    output_file << "中文:\n";

    while (count <= count_limit && std::getline(std::cin, line)) {
        // 检查内容是否包含 "Revert"
        if (line.find("Revert") != std::string::npos) {
            output_file << count << "." << line << std::endl; // 直接输出序号和内容
            count++;
            continue; // 处理下一行
        } 
        // 检查内容是否包含 "Merge"
        if (line.find("Merge") != std::string::npos) {
            continue; // 处理下一行
        }
        // 忽略 cc-XXXX 前的内容
        std::string content;
        if (std::regex_search(line, match, ccnc_regex)) {
            // 如果找到 ccnc-XXXX，提取内容
            content = line.substr(match.position() + match.length());
            // 去掉前后的空格
            content.erase(0, content.find_first_not_of(" \t"));
            content.erase(content.find_last_not_of(" \t") + 1);
            // 去掉可能的多余符号
            content.erase(std::remove(content.begin(), content.end(), ']'), content.end());
            // 去掉开头的冒号
            if (!content.empty() && content[0] == ':' ) {
                content.erase(0, 1); 
            }
            content.erase(0, content.find_first_not_of(" \t")); // 去掉冒号后面的空格
            // 处理内容，去掉冒号
            content.erase(std::remove(content.begin(), content.end(), ':'), content.end());
            // 输出到文件，序号和内容之间没有空格
            output_file << count << "." << content << std::endl; 
            // 处理多个ccnc-XXXX
            std::regex num_regex(R"(\|(ccnc-\d{3,4}))");
            std::string all_captures = "——ccnc-" + match[1].str();
            std::string remaining = line;
            // 从第一个匹配开始查找后续的 ccnc-XXXX
            std::smatch num_match;
            while (std::regex_search(remaining, num_match, num_regex)) {
                all_captures += num_match[0].str(); // 将后续捕获组拼接到字符串中

                // 更新 remaining 字符串，去掉已匹配的部分
                remaining = remaining.substr(num_match.position(0) + num_match.length(0));
            }
            // std::cout << all_captures << std::endl; // 测试输出
            output_file << all_captures << std::endl;
        } else {
            // 如果没有找到 ccnc-XXXX，查找 HYCCNC-XXXX
            std::regex hyccnc_regex(R"(HYCCNC-(\d{4})\s*\[Case\]\s*(.*))");
            std::smatch hyccnc_match;
            if (std::regex_search(line, hyccnc_match, hyccnc_regex)) {
                // 提取内容，从 [Case] 后第一个不为 " " 的字符开始
                std::string hyccnc_content = hyccnc_match[2].str();
                hyccnc_content.erase(0, hyccnc_content.find_first_not_of(" \t")); // 去掉前面的空格
                // 输出到文件，序号和内容之间没有空格
                output_file << count << "." << hyccnc_content << std::endl; // 确保没有换行
            }
        }
        count++;
    }

    output_file.close(); // 关闭文件
    return 1;
}
int pro2(int num,int num1)
{
    int count_limit = num;
    std::string line;
    int count = 1;

    // 正则表达式用于匹配 ccnc-XXXX 或 ccnc-XXX
    std::regex ccnc_regex(R"(ccnc-(\d{3,4})(?:\|(ccnc-\d{3,4}))*)");
    std::smatch match;

    // 创建输出文件
    std::ofstream output_file("/media/lxy/work/ccncResource/pcsh/releaseNoteAuto/releaseNote.txt",std::ios_base::app);
    if (!output_file) {
        std::cerr << "无法打开文件 releaseNote.txt" << std::endl;
        return 1;
    }

    while (count <= count_limit && std::getline(std::cin, line)) {
        // 检查内容是否包含 "Revert"
        if (line.find("Revert") != std::string::npos) {
            output_file << count + num1 << "." << line << std::endl; // 直接输出序号和内容
            count++;
            continue; // 处理下一行
        }
        // 检查内容是否包含 "Merge changes"
        if (line.find("Merge changes") != std::string::npos) {
            continue; // 处理下一行
        }
        // 忽略 cc-XXXX 前的内容
        std::string content;
        if (std::regex_search(line, match, ccnc_regex)) {
            // 如果找到 ccnc-XXXX，提取内容
            content = line.substr(match.position() + match.length());
            // 去掉前后的空格
            content.erase(0, content.find_first_not_of(" \t"));
            content.erase(content.find_last_not_of(" \t") + 1);
            // 去掉可能的多余符号
            content.erase(std::remove(content.begin(), content.end(), ']'), content.end());
            // 去掉开头的冒号
            if (!content.empty() && content[0] == ':' ) {
                content.erase(0, 1); 
            }
            content.erase(0, content.find_first_not_of(" \t")); // 去掉冒号后面的空格
            // 处理内容，去掉冒号
            content.erase(std::remove(content.begin(), content.end(), ':'), content.end());
            // 输出到文件，序号和内容之间没有空格
            output_file << count + num1 << "." << content << std::endl; 
            // 处理多个ccnc-XXXX
            std::regex num_regex(R"(\|(ccnc-\d{3,4}))");
            std::string all_captures = "——ccnc-" + match[1].str();
            std::string remaining = line;
            // 从第一个匹配开始查找后续的 ccnc-XXXX
            std::smatch num_match;
            while (std::regex_search(remaining, num_match, num_regex)) {
                all_captures += num_match[0].str(); // 将后续捕获组拼接到字符串中

                // 更新 remaining 字符串，去掉已匹配的部分
                remaining = remaining.substr(num_match.position(0) + num_match.length(0));
            }
            // std::cout << all_captures << std::endl; // 测试输出
            output_file << all_captures << std::endl;
        } else {
            // 如果没有找到 ccnc-XXXX，查找 HYCCNC-XXXX
            std::regex hyccnc_regex(R"(HYCCNC-(\d{4})\s*\[Case\]\s*(.*))");
            std::smatch hyccnc_match;
            if (std::regex_search(line, hyccnc_match, hyccnc_regex)) {
                // 提取内容，从 [Case] 后第一个不为 " " 的字符开始
                std::string hyccnc_content = hyccnc_match[2].str();
                hyccnc_content.erase(0, hyccnc_content.find_first_not_of(" \t")); // 去掉前面的空格
                // 输出到文件，序号和内容之间没有空格
                output_file << count + num1 << "." << hyccnc_content << std::endl; // 确保没有换行
            }
        }
        count++;
    }

    output_file.close(); // 关闭文件
    return 1;
}
int main(int argc, char* argv[]) {
    // 检查参数数量
    if (argc != 4) {
        std::cerr << "用法: " << argv[0] << " <需要读取的行数>" << std::endl;
        return 1;
    }
    int count_limit1 = std::stoi(argv[1]);
    int choice = std::stoi(argv[2]);
    int count_limit2 = std::stoi(argv[3]);
    if (choice == 1)
    {
        pro1(count_limit1);
    }
    else if (choice == 2)
    {
        pro2(count_limit1,count_limit2);
    }
    return 0;
}