# UVA154 - Recycling (回收)

## 题目描述

每个城市有5个回收箱，分别用于回收纸张(P)、玻璃(G)、易拉罐(C)、报纸(N)和垃圾填埋(L)。每个城市对这5种材料在5个回收箱中的偏好顺序不同。

输入格式：
- 多个测试用例，以`#`结束
- 每个城市由一个字母代码描述，后跟5行
- 每行格式如`P 1 3 2 4 5`，表示材料P在箱1的偏好等级为1，箱2为3，箱3为2，箱4为4，箱5为5
- 测试用例之间有空行分隔

输出要求：
- 按回收行为从好到差排序（最高的"第一偏好"总分优先）
- 每行输出一个城市代码

## 解题思路

### 问题分析

每个城市有5种材料，每种材料在5个箱子里有一个偏好等级（1-5，每个等级恰好使用一次）。需要计算每个城市的"回收行为得分"，然后按得分降序排序。

关键点：
- 理解"第一偏好"的含义：对于每种材料，找出将其排在第一位（等级1）的箱子
- 得分计算：将每个材料的第一偏好箱子编号相加
- 得分越高表示回收行为越好（偏好分布越分散）

### 核心思路

1. 解析每个城市的5行数据
2. 对每种材料，找出偏好等级为1的箱子编号
3. 将所有材料的第一偏好箱子编号相加得到总分
4. 按总分降序排序，同分按城市代码升序排序

### 算法流程

```
1. 读取输入，处理多个测试用例
2. 对每个城市：
   a. 读取城市代码
   b. 循环5次读取每种材料的偏好数据
   c. 解析每行：材料字符 + 5个等级数字
   d. 对每个等级，如果是1，将对应箱子编号加入总分
3. 存储所有城市及其得分
4. 排序：得分降序，同分按代码升序
5. 输出排序后的城市代码
```

### 复杂度分析

- 时间复杂度：O(N log N)，其中N是城市数量（排序复杂度）
- 空间复杂度：O(N)，存储所有城市数据

## 代码实现

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct City {
    char code;
    int score;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    vector<City> cities;
    
    while (getline(cin, line) && line[0] != '#') {
        if (line.empty()) continue;
        
        City city;
        city.code = line[0];
        city.score = 0;
        
        for (int i = 0; i < 5; i++) {
            getline(cin, line);
            char mat;
            int r1, r2, r3, r4, r5;
            sscanf(line.c_str(), "%c %d %d %d %d %d", &mat, &r1, &r2, &r3, &r4, &r5);
            
            if (r1 == 1) city.score += 1;
            if (r2 == 1) city.score += 2;
            if (r3 == 1) city.score += 3;
            if (r4 == 1) city.score += 4;
            if (r5 == 1) city.score += 5;
        }
        
        cities.push_back(city);
    }
    
    sort(cities.begin(), cities.end(), [](const City& a, const City& b) {
        if (a.score != b.score) return a.score > b.score;
        return a.code < b.code;
    });
    
    for (const auto& city : cities) {
        cout << city.code << "\n";
    }
    
    return 0;
}
```

## 测试样例

**输入：**
```
a
P 1 5 2 4 3
G 2 1 5 4 3
C 3 2 1 4 5
N 4 3 2 1 5
L 5 4 3 2 1

b
P 1 2 3 4 5
G 2 3 4 5 1
C 3 4 5 1 2
N 4 5 1 2 3
L 5 1 2 3 4

#
```

**输出：**
```
a
b
```

**解释：**
- 城市a：P在箱1等级1(+1)，G在箱2等级1(+2)，C在箱3等级1(+3)，N在箱4等级1(+4)，L在箱5等级1(+5)，总分15
- 城市b：P在箱1等级1(+1)，G在箱5等级1(+5)，C在箱4等级1(+4)，N在箱3等级1(+3)，L在箱2等级1(+2)，总分15
- 两城市同分，按代码升序排列