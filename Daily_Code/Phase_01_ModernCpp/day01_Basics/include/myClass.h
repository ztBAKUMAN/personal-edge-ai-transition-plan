#pragma once
#include <list>
#include <vector>
#include <utility>
#include <string>

//** C++的底层设计理念与关键字**//
// 存在性: 声明、定义、初始化
// 时空观: 作用域、生命周期、链接属性
// 控制权: 隐式默认或显式
// 物质性: 左值、右值
// 责任制: RAII与所有权
// 决策期: 静态派发、动态派发
// 边界线: 未定义行为

// 外部声明, 告诉编译器存在一个exNum变量, 使用时可以去其他地方找
extern int exNum;
// 通常只在头文件声明, 如果定义且被多次包含会产生编译错误(重复定义)
// C++17允许使用inline对头文件的全局变量进行定义, 保证全局唯一性
inline int g_num = 0;
inline constexpr int gc_num = 0;
// inline对内部全局变量定义(C++17),
// 语法正确但冗余, 等同于static int
// 不会报重定义错误, 因为每一个包含此头文件的单元都会拷贝一份同名变量, 浪费资源
inline static int s_num = 0;


// 命名空间, 避免多文件命名冲突, 模块化隔离
namespace MySpace{
    // 定义结构体, 作用与class一样, 默认public属性
    struct MyData{
        // 通常只用于数据定义和存储, 不包含方法
        int index;
        std::vector<std::pair<int, int>> vecData;
    };

    // 枚举类型, 代替抽象的数字, 提高可读性
    // 限制取值范围
    // 加入class避免隐式转换
    enum class ErrType{
        EM_TIMEOUT,
        EM_CONNECT,
        EM_FAILED
    };

    // 子命名空间加入inline, 可使父命名空间直接访问内部
    // 直接调用MySpace::function()
    inline namespace FuncSpace{
        void function();
    }
}

// 简化命名空间
namespace mf = MySpace::FuncSpace;

// 用using使当前作用域内默认使用命名空间(避免在头文件直接引入整个namespace)
// 后续直接写MyData, 而无需使用MySpace::MyData
using namespace MySpace;
// 只引入命名空间中一个成员
using MySpace::ErrType;
// using enum 同理(C++20引入)

// typedef传统取别名
typedef std::vector<int> vecInt;
// using现代别名
using vecInt = std::vector<int>;
// using模板别名
template<typename T>
using Vec = std::vector<T>;

// 自定义类
class MyClass{
public:
    MyClass();
    // 避免隐式转换
    explicit MyClass(int num);
    ~MyClass();
    // 内联函数(适用于简单函数)
    // const告诉编译器不会修改成员变量
    inline int getMyClassNum() const {return m_num;}
    // const引用作为参数类型可避免拷贝
    void setNumList(const std::list<int>& numList);
    void coutList();

private:
    void init();
private:
    // 成员变量声明
    int m_num{10};             // c++11 初始化器, 相当于提供默认值
    std::list<int> m_list;

    /**传统C++**/
    // 类内static声明(不受访问符限制)
    // 普通静态成员, 不能类内初始化
    static int m_Int;
    // 静态const成员, 只有整型类内初始化
    static const int m_cInt = 0;
    static const double m_cDouble;

    /**C++11/14**/
    // 可以使用constexpr对非整型静态成员初始化(仅限于基本类型)
    static constexpr double m_csDouble = 0.9;

    /**C++17**/
    // 引入inline彻底解决静态初始化问题
    // 加入inline的初始化是真正的定义, 在这之前的初始化只是一种声明(提供了初始化器指定默认值)
    inline static int m_iInt = 0;   // 普通静态成员初始化
    inline static const std::string m_name = "mike";    // 复杂类型静态const成员初始化

};

// 继承类
class MyDerived : public MyClass{
public:
    // 继承父类构造函数
    using MyClass::MyClass;
    explicit MyDerived(double num);
    ~MyDerived();
private:
    double m_num;
};