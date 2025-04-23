# ticketmap

## 1. 简介

**一个具有强大功能的容器**

它是作者开发出来的一个扩展库

[^陈佳宇]: 拿到这个项目刚开始以为是邮票地图？再参阅了文档、调试环境去运行后，发现它其实是一个非常酷的容器，类似map, unordered_map，一个全新的map



## 2. 功能特点

1. 自动键功能管理：自动为每个新插入的元素分配唯一的键（票号）。
2. 键溢出处理：当键类型达到最大值时，能够检测溢出并抛出异常。
3. 迭代器支持：提供迭代器以遍历容器中的所有元素。
4. 容量管理：可以预留足够的空间以存储指定数量的元素。
5. 异常处理：在遇到错误情况（如键溢出）时抛出异常。



## 3. ticketmap的定义及方法

**ticketmap的定义同map, unordered_map一样**

~~~cpp
// 声明
ticket_map<int, string> 变量名;
~~~

**方法：**
~~~cpp
// insert("值") -- 给键插入值
auto 键 = 变量名.insert(值);
// 例
auto ticket = map.insert("Hello World!");
cout << ticket << endl;
// 这里输出0 因为ticket从0自增
cout << map[ticket] ;
// 这里会输出答案值:Hello World!
~~~

~~~cpp
// map.begin() - 返回迭代器的第一个参数

auto one = map.insert("one");
auto two = map.insert("two");
auto three = map.insert("three");

cout << map.begin().ticket << ' ' << map.begin().value << endl;
// 答案输出为 0 one. 因为是添加的第一个键和它的值
~~~



## 4. 使用示例



```markdown
#include "ticket_map.hpp"
#include <iostream>

// 个人习惯：使用命名空间简写代码
using namespace jss; // jss::ticket_map 变为 ticket_map
using namespace std; // std::cout 变为 cout

int main() {
    // 创建一个 ticket_map 实例，键类型为 int，值类型为 string
    ticket_map<int, string> map;

    // 插入元素并获取分配的票号
    auto ticket = map.insert("Hello, World!");
    cout << "Inserted with ticket: " << ticket << endl;

    // 通过票号访问元素
    cout << "Value: " << map[ticket] << endl;

    // 遍历容器中的所有元素
    for (const auto& entry : map) {
        cout << "Ticket: " << entry.ticket << ", Value: " << entry.value << endl;
    }

    return 0;
}
```

**运行结果：**

![1745249897527](/imges/run_problem1.png)



## 5. 运行时候出现的小问题

**第一次在运行的时候出现一个小问题（图1）**

![1745248916445](.\imges\run_problem1.png)

**利用Kimi找到了解决这个问题的办法**

![1745249350575](.\imges\run_solution.png)



## 6. 环境配置

- 该项目作为c++的一个拓展项目并不需要配置什么环境，只需要提供能编译G++17的编译器

- 只要把项目拉取下来，然后在编译的c++文件中去导入这个库，即可使用

  ​												<!--陈佳宇-->
