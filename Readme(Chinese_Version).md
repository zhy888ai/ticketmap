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

## 7.翻译

### 1~80行（管理单调递增的 ID 与对应值之间的映射关系）

```cpp
// This code is released under the Boost Software License
// https://www.boost.org/LICENSE_1_0.txt
// (C) Copyright 2021 Anthony Williams

// 此代码根据 Boost 软件许可证发布
// https://www.boost.org/LICENSE_1_0.txt
// (C) 版权所有 2021 Anthony Williams
```

```cpp
/// A map between from Ticket values to Value values.
///
/// Ticket must be default-constructible, incrementable, less-than
/// comparable and equality-comparable. Value must be move-constructible
///
/// When new values are inserted they are assigned new Ticket values
/// automatically. If the Ticket value overflows then no more values can be
/// inserted.

/// 一个从票证值到值之间的映射。

///
/// 票证类型（Ticket）必须是可默认构造的、可递增的、可进行小于比较的以及可进行相等比较的。值类型（Value）必须是可移动构造的。
///
/// 当插入新值时，它们会自动被分配新的票证值。如果票证值溢出，那么就不能再插入更多的值。
```

template <typename Ticket, typename Value> class ticket_map {
    static_assert(
        std::is_default_constructible<Ticket>(),
        "票证类型（Ticket）必须是可默认构造的");
    static_assert (
        std::is_same_v<decltype (std::declval<Ticket &>()++), Ticket>,
        "票证类型（Ticket）必须是可后置递增的");
    static_assert (
        std::is_same_v<
            decltype (std::declval<Ticket &>() < std::declval<Ticket &>()),
            bool>,
        "票证类型（Ticket）必须是可进行小于比较的");
    static_assert (
        std::is_same_v<
            decltype (std::declval<Ticket &>() == std::declval<Ticket &>()),
            bool>,
        "票证类型（Ticket）必须是可进行相等比较的");
    static_assert (
        std::is_same_v<
            decltype (std::declval<Ticket &>() != std::declval<Ticket &>()),
            bool>,
        "票证类型（Ticket）必须是可进行不等比较的");



```cpp
/// The type of the actual storage 
/// 实际存储的类型
```

   

 using collection_type=
        std::vector<std::pair<Ticket, std::optional<Value>>>;

```cpp
/// The iterator for our map
/// 我们映射的迭代器
```

   

 template <bool is_const> class iterator_impl {
        using dereference_type=
            std::conditional_t<is_const, Value const &, Value &>;
    

```cpp
public:
            /// The value_type of our iterator is a ticket/value pair. We use
            /// references, since the underlying storage doesn't hold the same
            /// member types
            struct value_type {
            /// A reference to the ticket value for this element
                Ticket const &ticket;
            /// A reference to the data value for this element
                dereference_type value;
            };
public:
            /// 我们迭代器的 value_type 是一个票证 / 值对。我们使用引用，因为底层存储并不持有相同的成员类型
        	struct value_type {
            /// 对此元素的票证值的引用
            	Ticket const &ticket;
            /// 对此元素的数据值的引用
            	dereference_type value;
      	 	};
```

```cpp
private:
            /// It's an input iterator, so we need a proxy for ->
            struct arrow_proxy {
            /// Our proxy operator->
                value_type *operator->() noexcept {
                    return &value;
                }
            /// The pointed-to value
                value_type value;
            };
private:
       	   /// 它是一个输入迭代器，所以我们需要一个用于 -> 的代理
           struct arrow_proxy {
            /// 我们的代理操作符 ->
            value_type *operator->() noexcept {
                return &value;
            	}
            /// 被指向的值
            	value_type value;
        	};
```



<!--by 张皓煜-->

### 80~125行（类型定义注释）
- `Required iterator typedefs`  
  `所需的迭代器类型定义`
- `Compare iterators for inequality.`  
  `比较迭代器是否不相等`
- `Equality in terms of iterator_impls: if it's not not-equal then it must be equal`  
  `就迭代器实现而言的相等性：如果不是不相等，那么它必须相等`
- `Dereference the iterator`  
  `取消引用迭代器`
- `Dereference for iter->m`  
  `对 iter->m 进行解引用（即通过指针/迭代器访问成员 m）`
- `Pre-increment`  
  `前置递增`
- `Post-increment`  
  `后增量`

---

### 127~138行（构造方法注释）
- `Allow constructing a const_iterator from a non-const iterator, but not vice-versa`  
  `允许从非const迭代器构造const迭代器，但反之不可。`
- `A default-constructed iterator is a sentinel value`  
  `默认构造的迭代器是一个哨兵值`

---

### 140~160行（实现细节注释）
- `Construct from an iterator into a map`  
  `通过迭代器构造映射`
- `The stored iterator`  
  `存储的迭代器`
- `The map`  
  `映射`

---

### 80~160行中代码特殊实现说明
- `arrow_proxy operator->()`  
  `通过指针代理访问元素成员（实现 iter->m 语法）`
- `underlying_iterator` 类型说明  
  `底层容器迭代器（根据 is_const 选择 const/non-const 版本）`
- `map_ptr` 类型说明  
  `指向所属容器的指针`
  <!--by 陈蓉蓉-->

### 400-480行翻译
1. Return the maximum number of items that can be inserted without
 reallocating
**返回在不需要重新分配内存的情况下可以插入的最大项目数。**
2. Return the number of entries for a ticket in the container. Thereturn value is 1 if the ticket is in the container, 0 otherwise.
**返回容器中票证的条目数量。如果票证在容器中，则返回值为1，否则为0。**
3. Erase an entry referenced by an iterator into the internal vector
**删除内部向量中由迭代器引用的条目**
4. Returns true if the container has too many empty slot, falseotherwise
**如果容器中有太多空槽，则返回true，否则返回false。**
5. Compact the container to remove all empty slots.
**压缩容器以移除所有空槽**
6. Increment a ticket and check for overflow (generic)
**增加票证并检查溢出（通用）**
<br>
<!-- by 陈桂生 -->

# 原Readme翻译

## 票证映射

我遇到了一个越来越常见的场景：你有一些单调递增的 ID，比如订阅号、连接索引或用户 ID，并且你的 C++ 程序需要保存与该 ID 值相关联的一些数据。然后，程序可以传递这个 ID，并在稍后使用该 ID 来访问相关数据。

随着时间的推移，ID 可能会失效，因此与该值相关联的数据会被移除，最终你会得到一组稀疏的当前活动 ID。因此，你自然会倾向于使用一个映射（无论是`std::map`、`std::unordered_map`还是其他自定义映射）来将数据与 ID 关联起来。

通常，这样的映射是作为基于节点的容器实现的，这意味着节点可能会被分配到不同的内存地址，这对缓存性能不利。添加和删除节点也总是需要进行内存分配 / 释放操作。

在他的["更好的代码：关系"](https://sean-parent.stlab.cc/papers-and-presentations/#better-code-relationships)演讲中，Sean Parent 描述了一种替代实现，他称之为 "俄罗斯大衣寄存算法"。在这个算法中，映射被实现为一个键 / 可选数据对的向量。因为键来自单调递增的索引，所以向量*始终是有序的*，并且插入总是在末尾进行。条目可以通过清除数据来删除，如果有太多空条目，则可以压缩向量。查找总是很快，因为向量始终是有序的，所以简单的二分查找就能找到正确的元素。

这个库是该算法的一个实现，我称之为*票证映射*：它将一个*票证*映射到一个*值*。当你插入一个值时，它会被分配下一个可用的票证值。你可以稍后使用该票证来访问或删除该值。



## 许可证

本代码根据[Boost 软件许可证](https://www.boost.org/LICENSE_1_0.txt)发布：

> Boost 软件许可证 - 版本 1.0 - 2003 年 8 月 17 日
>
> 特此免费授予任何获得本许可证所涵盖的软件及随附文档（"软件"）的个人或组织使用、复制、展示、分发、执行和传输该软件的权利，并允许其准备该软件的衍生作品，并允许向其提供软件的第三方也这样做，但需遵守以下规定：
>
> 软件中的版权声明和本完整声明（包括上述许可证授予、本限制和以下免责声明）必须包含在软件的所有副本（全部或部分）以及软件的所有衍生作品中，除非此类副本或衍生作品仅以由源语言处理器生成的机器可执行目标代码的形式存在。
>
> 软件按 "原样" 提供，不提供任何形式的保证，无论是明示的还是暗示的，包括但不限于适销性、特定用途适用性、标题和不侵权的保证。在任何情况下，版权持有人或任何分发软件的人对于任何损害或其他责任（无论是合同责任、侵权责任还是其他责任）概不负责，无论该责任是因软件或其使用或其他交易而产生、源于或与之相关。



<!--by 张皓煜-->

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