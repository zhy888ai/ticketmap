//
// Created by JYC on 2025/4/22.
//
#include "/ticket_map.hpp"
#include <iostream>

int main() {
    jss::ticket_map<int, std::string> map;  // 明确使用 jss:: 前缀

    // 插入元素并获取分配的票号
    auto ticket = map.insert("Hello, World!");
    std::cout << "Inserted with ticket: " << ticket << std::endl;

    // 通过票号访问元素
    std::cout << "Value: " << map[ticket] << std::endl;

    // 遍历容器中的所有元素
    for (const auto& entry : map) {
        std::cout << "Ticket: " << entry.ticket << ", Value: " << entry.value << std::endl;
    }

    return 0;
}
// 陈佳宇
