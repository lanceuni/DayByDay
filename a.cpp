#include <iostream>
#include <cstdint>

int main() {
    uint8_t val = 8;       // ASCII Backspace
    uint8_t visible = 65;  // ASCII 'A'

    std::cout << "Start";
    std::cout << val ;      // 输出退格字符
    std::cout << "End\n";  // 退格后，E覆盖了t

    std::cout << "Visible: ";
    std::cout << visible << std::endl;  // 输出 'A'
    std::cout << +visible << std::endl;  // 输出 '65'
    std::cout << static_cast<int>(visible) << std::endl;  // 输出 'A'
}