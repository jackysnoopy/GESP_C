/**
 * UVA105 - The Skyline Problem
 * 天际线问题
 * 
 * 解法：扫描线 + multiset
 * 将每个建筑拆分为两个事件：左端点(加入高度)和右端点(移除高度)
 * 按x坐标排序，用multiset维护当前活跃的高度
 * 当最大高度发生变化时，记录天际线的关键点
 */
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct Event {
    int x;      // x坐标
    int h;      // 高度（正数表示加入，负数表示移除）
    bool isLeft; // 是否是左端点
    
    // 排序规则：x升序，左端点优先于右端点
    bool operator<(const Event& other) const {
        if (x != other.x) return x < other.x;
        return isLeft > other.isLeft;
    }
};

int main() {
    vector<Event> events;
    int l, h, r;
    
    // 读取所有建筑数据
    while (cin >> l >> h >> r) {
        events.push_back({l, h, true});   // 左端点，加入高度h
        events.push_back({r, -h, false}); // 右端点，移除高度h
    }
    
    // 按规则排序
    sort(events.begin(), events.end());
    
    multiset<int> heights; // 维护当前活跃的高度
    heights.insert(0);     // 地面高度为0
    
    vector<pair<int, int>> skyline; // 天际线结果
    int prevMax = 0;                // 上一次的最大高度
    
    for (const auto& e : events) {
        if (e.isLeft) {
            // 左端点：加入该建筑的高度
            heights.insert(e.h);
        } else {
            // 右端点：移除该建筑的高度
            heights.erase(heights.find(-e.h));
        }
        
        // 获取当前最大高度
        int currMax = *heights.rbegin();
        
        // 如果最大高度发生变化，记录天际线点
        if (currMax != prevMax) {
            skyline.push_back({e.x, currMax});
            prevMax = currMax;
        }
    }
    
    // 输出结果
    for (size_t i = 0; i < skyline.size(); ++i) {
        if (i > 0) cout << " ";
        cout << skyline[i].first << " " << skyline[i].second;
    }
    cout << endl;
    
    return 0;
}
