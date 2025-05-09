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


### 标准迭代器类型定义
- ` Standard iterator typedef`
  `标准迭代器类型定义`
- ` Standard const_iterator typedef `
` 标准常量迭代器类型定义`

### 空映射构造
-  ` Construct an empty map  `
`构造一个空映射`

### 范围构造
- ` Construct a map from a range of elements `
`从元素范围构造映射`

### 移动构造
-  `Move-construct from other. The elements of other are transferred to this; other is left empty 到 **this**` 
`从其他对象移动构造。将其他对象的元素转移到新对象，原对象变为空`

### 拷贝构造
-  `Copy-construct from other. this will have the same elements and next ticket value as other. `
`从另一个对象复制构造。新对象包含与原对象相同的元素和下一个票证值`

### 拷贝赋值
-  `Copy-assign from other `
`拷贝赋值操作`

### 移动赋值
-  `Move-assign from other `
`移动赋值操作`

### 成员函数 empty()
-  `Returns true if there are no elements currently in the map, false otherwise`
 `返回当前映射是否为空`

### size()
-  `Returns the number of elements currently in the map `
 `返回当前映射的元素数量`

### insert(value)
-   `Insert a new value into the map. It is assigned a new ticket value.`
`插入新值到映射。分配新票证值`
-  ` Returns the ticket for the new entry. `
`返回新条目的票证`
-  `Invalidates any existing iterators into the map. `
`使所有现有迭代器失效`
-  `Throws overflow_error if the Ticket values have overflowed. `
`票证溢出时抛出 overflow_error 异常`

### insert(range)
-  ` Insert a set of new values into the map. Each is assigned a new   ticket value. `
`批量插入新值。每个元素分配新票证值。`
- `Returns an iterator that references the first new  or end() if no values were inserted. `
`返回指向第一个新插入元素的迭代器（若无插入则返回 end()）`
-  `Invalidates any existing iterators into the map. `
`使所有现有迭代器失效`
-  `Throws overflow_error if the Ticket values have overflowed. `
`票证溢出时抛出 overflow_error 异常`

### emplace(args...)
-  `Insert a new value into the map, directly constructing in place.`
`将一个新值插入映射中，并直接在原地构造。`
-  `It  is assigned a new ticket value. Returns the ticket for the new  entry.`
 `它被分配了一个新的票证值。返回新条目的票证。`
-  ` Invalidates any existing iterators into the map. `
`使所有现有迭代器失效`
-  `Throws overflow_error if the Ticket values have overflowed. `
`票证溢出时抛出 overflow_error 异常`

 <!--by 龚祀玲-->