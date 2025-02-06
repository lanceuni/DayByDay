#include <iostream>
#include <cstring>

// 缓冲区溢出 ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7fff98d80dfa at pc 0x7edb3f23a2c3 bp 0x7fff98d80dc0 sp 0x7fff98d80568
void bufferOverflow() {
    std::cout << "Starting buffer overflow test..." << std::endl;
    char buffer[10]; // 分配一个大小为10的字符数组
    // 故意复制超过缓冲区大小的字符串到buffer中
    // strlen("Hello, World!") 是 13，包括结尾的空字符'\0'，但buffer只有10个字节
    strcpy(buffer, "Hello, World!");
    // 这里不会执行到，因为上面的strcpy很可能已经导致程序崩溃了
    std::cout << "Buffer content: " << buffer << std::endl;
}
//访问无效内存 ERROR: AddressSanitizer: heap-use-after-free on address 0x602000000010 at pc 0x59a4a78e35cf bp 0x7ffd23928a30 sp 0x7ffd23928a20
void invalidMemoryAccess() {
    int* ptr = new int(42); // 动态分配一个整数
    std::cout << "The value is: " << *ptr << std::endl;

    delete ptr; // 释放内存
    // 现在 ptr 指向的内存已经被释放了，但我们还尝试访问它
    std::cout << "The value after deletion is: " << *ptr << std::endl;}
#include <iostream>

// 内存泄漏 ERROR: LeakSanitizer: detected memory leaks
void leakMemory() {
    std::cout << "Creating memory leak..." << std::endl;
    // 动态分配一个整型数组，但随后不释放它
    int* array = new int[100];
    // 不调用delete[] array;
    std::cout << "Memory leak created. Program will now exit." << std::endl;
}

int main() {
    // invalidMemoryAccess();
    // bufferOverflow();
    // leakMemory();
}

