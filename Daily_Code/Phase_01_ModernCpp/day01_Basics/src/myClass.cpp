#include "myClass.h"
#include <mutex>
#include <iostream>

// 类外初始化
int MyClass::m_Int = 0;
const double MyClass::m_cDouble = 0.1;

// 默认仅内部可见的只读全局变量
// 加上extern可改为外部链接属性
const int g_count = 10;

// 表示内部可读写的全局变量
static int stNum = 1;
// 或者使用匿名空间有同样效果
namespace {
    int spaceNum = 1;
}

// 可被外部访问的全局变量定义
int exNum = 100;

MyClass::MyClass()
{
    m_num = 0;
    init();
}
MyClass::MyClass(int num) : m_num(num)
{
    init();
}
MyClass::~MyClass()
{

}

void mf::function()
{
    
}

void MyClass::coutList()
{
    for(auto num : m_list)
    {
        std::cout << " " << num;
    }
}
void MyClass::setNumList(const std::list<int>& numList)
{
    m_list = numList;
}

void MyClass::init()
{
    // 局部静态变量
    // 作用域只在函数内部, 但生命周期为整个程序运行期
    static int staticNum = 10;
    
    m_list.clear();
    for(int i = 0; i < g_count; ++i)
    {
        m_list.push_back(i);
    }
}

MyDerived::MyDerived(double num) : m_num(num)
{

}

MyDerived::~MyDerived()
{

}