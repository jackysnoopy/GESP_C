# UVA145 - Gondwanaland Telecom (冈瓦纳电信)

## 题目描述
计算电话通话费用，根据通话时段和日期（工作日或周末）确定费率。
三个城市（Gondwanaland, Centreville, Snowfall）的费率表如下：
- Gondwanaland: A=0.10, B=0.06, C=0.02
- Centreville: A=0.25, B=0.15, C=0.05
- Snowfall: A=0.53, B=0.33, C=0.13

费率时段：
- A (Day): 8:00-18:00
- B (Evening): 18:00-22:00
- C (Night): 22:00-8:00

输入格式：城市代码 开始时间 结束时间（每个测试用例一行，以"#"结束）
输出格式：城市代码 开始时间 结束时间 总分钟数 总费用（每个测试用例一行）

## 解题思路

### 问题分析
需要根据给定的开始和结束时间计算通话费用，费率取决于城市和通话时段。
注意：结束时间可能在第二天（即跨天通话），需要正确处理时间计算。

### 核心思路
1. 将时间转换为分钟数以便计算。
2. 对于每个分钟，根据当前时间确定费率时段（A、B或C）。
3. 累加总分钟数和总费用。

### 算法流程
1. 读取城市代码、开始时间和结束时间。
2. 将开始时间和结束时间转换为分钟数（从0点开始计算）。
3. 如果结束时间小于等于开始时间，说明通话跨天，将结束时间加上24*60分钟。
4. 确定城市对应的费率表索引。
5. 遍历从开始到结束的每一分钟，计算该分钟的费率并累加。
6. 输出结果。

### 复杂度分析
- 时间复杂度：O(n)，其中n是通话总分钟数。最坏情况下可能需要计算24*60=1440分钟。
- 空间复杂度：O(1)。

## 代码实现
```cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

const double rates[3][3] = {
    {0.10, 0.06, 0.02},  // Gondwanaland
    {0.25, 0.15, 0.05},  // Centreville
    {0.53, 0.33, 0.13}   // Snowfall
};

int timeToMinutes(const string& time) {
    int h = stoi(time.substr(0, 2));
    int m = stoi(time.substr(3, 2));
    return h * 60 + m;
}

int getTimePeriod(int minutes) {
    int hour = minutes / 60;
    if (hour >= 8 && hour < 18) return 0;
    if (hour >= 18 && hour < 22) return 1;
    return 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string city_code, start_time, end_time;
    while (cin >> city_code >> start_time >> end_time && city_code != "#") {
        int start_minutes = timeToMinutes(start_time);
        int end_minutes = timeToMinutes(end_time);
        
        if (end_minutes <= start_minutes) {
            end_minutes += 24 * 60;
        }
        
        int city_index = 0;
        if (city_code == "C") city_index = 1;
        else if (city_code == "S") city_index = 2;
        
        int total_minutes = 0;
        double total_cost = 0.0;
        
        for (int t = start_minutes; t < end_minutes; ++t) {
            int period = getTimePeriod(t % (24 * 60));
            total_cost += rates[city_index][period];
            ++total_minutes;
        }
        
        cout << setw(3) << city_code << " " 
             << setw(8) << start_time << " " 
             << setw(8) << end_time << " " 
             << setw(6) << total_minutes << " " 
             << fixed << setprecision(2) << total_cost << endl;
    }
    
    return 0;
}
```
