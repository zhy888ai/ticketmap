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

![1745248916445](/imges/run_problem1.png)

**利用Kimi找到了解决这个问题的办法**

![1745249350575](/imges/run_solution.png)



## 6. 环境配置

- 该项目作为c++的一个拓展项目并不需要配置什么环境，只需要提供能编译G++17的编译器

- 只要把项目拉取下来，然后在编译的c++文件中去导入这个库，即可使用

- 如果直接拉取不可以的话或许是没有配置MinGW，这边我使用的是Clion，下载Clion会自带默认MinGW，如果还出现报错的话，那就把进入到MinGW的bin目录当中把地址复制到环境变量->系统变量->path中去配置 

  <!--陈佳宇-->

 ### 插入操作注释
- `Insert a new value into the map, directly constructing in place. It is assigned a new ticket value. Returns the ticket for the new entry. Invalidates any existing iterators into the map. Throws overflow_error if the Ticket values have overflowed.`  
  `插入一个新值到映射中，在原地直接构造。它会被分配一个新的票据值。返回新条目的票据。会使映射中现有的任何迭代器失效。如果票据值已溢出，则抛出溢出异常。`

### 查找操作注释
- `Find a value in the map by its ticket. Returns an iterator referring to the found element, or end() if no element could be found`  
  `通过票证在映射中查找值。返回指向找到元素的迭代器，如果未找到元素则返回 end()`

- `Find a value in the map by its ticket. Returns a reference to the found element. Throws std:out_of_range if the value was not present.`  
  `通过票证在映射中查找值。返回指向找到元素的引用。如果值不存在，则抛出 std::out_of_range 异常。`

### 迭代器操作注释
- `Returns an iterator to the first element, or end() if the container is empty`  
  `返回指向第一个元素的迭代器，如果容器为空则返回 end()`

- `Returns an iterator one-past-the-end of the container`  
  `返回指向容器末尾后一个元素的 const_iterator`

- `Returns a const_iterator to the first element, or end() if the container is empty`  
  `返回指向第一个元素的 const_iterator。如果容器为空则返回 cend()`

- `Returns a const_iterator one-past-the-end of the container`  
  `返回指向容器末尾后一个元素的 const_iterator`

### 删除操作注释
- `Remove an element with the specified ticket. Returns an iterator to the next element if there is one, or end() otherwise. Returns end() if there was no element with the specified ticket. Invalidates any existing iterators into the map. Compacts the data if there are too many empty slots.`  
  `删除具有指定票证的元素。如果存在下一个元素，则返回指向下一个元素的迭代器，否则返回 end()。如果未找到具有指定票证的元素，则返回 end()。删除元素会使得所有现有的映射迭代器失效。如果存在过多的空闲槽位，则压缩数据。`

### 特殊机制注释
- `Invalidates any existing iterators`  
  `会使现有迭代器失效`

- `Throws overflow_error`  
  `抛出溢出异常`

- `Compacts the data`  
  `压缩数据`
       

### 使用Deepseek（AI）工具以及修改
![17452498975](/imges/2208305020346_1.png)

![17452498952](/imges/2208305020346_2.png)

![17452498852](/imges/2208305020346_3.png)
<!--岑允欣-->    

        