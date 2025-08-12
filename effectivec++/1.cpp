#include <iostream>

namespace Term2
{
//define常量不会进入记号表symbol table，会被预处理器变成数字，于是编译信息中的1.653让人困惑来源。
#define ASPECT_RATIO 1.650
const double ASPECT_RATIO1 = 1.651;
//定义常量指针
const char* const authorname = "luozhen";
const std::string authorname1("luozhen");
//class常量，static变成静态成员变量。
class GamePlayer{
private:
    static const int numTurns = 5;
    static constexpr double ASPECT_RATIO2 = 1.652;
    int scores[numTurns];
    /*不允许static in class初始化,也可以enum hack.原理:枚举类型的数值可以当作ints使用
    enum值不可以取地址：因为枚举类型的数值在编译时就已经确定,不可以改变
    enum hack,是模版元编程的基础技术。*/
    enum {NumTurns = 5};
    int Scores[NumTurns];
};

const int GamePlayer::numTurns;//定义式

//宏函数macro 尽量使用inline；文本替换可能导致表达式作为参数时多次计算。
#define MAX(a,b) ((a)>(b)?(a):(b))
template<typename T>
inline T max(T a, T b) { return a > b ? a : b; }
} // namespace Term2

int main()
{
    int a =5,b =0;
    auto ret = MAX(++a,b);  // 注意：宏会导致++a执行两次,((++a) > (0) ? (++a) : (0))
    std::cout<<"ret:"<<ret<<" a:"<<a<<std::endl; 
    ret = MAX(++a,b+10);    // 这里++a会执行1次 ((++a) > (0+10) ? (++a) : (0+10))
    std::cout<<"ret:"<<ret<<" a:"<<a<<" b:"<<b<<std::endl;
    return 0;
}

namespace Term3{


} // namespace Term3