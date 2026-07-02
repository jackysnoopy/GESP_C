#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int k, m, n;
    cin >> k >> m >> n;
    
    vector<long long> p(k), t(k);
    for (int i = 0; i < k; i++) cin >> p[i] >> t[i];
    
    vector<long long> f(m);
    for (int i = 0; i < m; i++) cin >> f[i];
    
    // 按位置排序草地和对手奶牛
    vector<int> grassIdx(k);
    for (int i = 0; i < k; i++) grassIdx[i] = i;
    sort(grassIdx.begin(), grassIdx.end(), [&](int a, int b) {
        return p[a] < p[b];
    });
    
    sort(f.begin(), f.end());
    
    // 对于每块草地，计算如果Farmer John的奶牛最近能获得的价值
    // 贪心：用线段树或二分
    
    // 简单方法：对于每块草地，找最近的对手奶牛
    // 如果Farmer John放奶牛更近，则获得价值
    
    // 计算每块草地被谁拥有（没有Farmer John奶牛时）
    vector<long long> grassValue(k, 0);
    for (int i = 0; i < k; i++) {
        int gi = grassIdx[i];
        long long pos = p[gi];
        
        // 找最近的对手奶牛
        auto it = lower_bound(f.begin(), f.end(), pos);
        long long dist = 1e18;
        if (it != f.end()) dist = min(dist, *it - pos);
        if (it != f.begin()) dist = min(dist, pos - *(it - 1));
        
        // 如果Farmer John在草地位置放奶牛，距离为0，一定能获得
        // 但需要检查是否与对手奶牛位置冲突
        bool conflict = false;
        for (long long fp : f) {
            if (fp == pos) { conflict = true; break; }
        }
        
        if (!conflict) {
            grassValue[gi] = t[gi];
        }
    }
    
    // 贪心：Farmer John放n头奶牛在最有价值的位置
    // 每头奶牛可以"覆盖"一片区域
    
    // 简单方法：计算每块草地的"额外价值"
    // 如果Farmer John在草地i附近放奶牛，可以获得t[i]
    // 但不能与对手奶牛位置冲突
    
    vector<long long> extra(k, 0);
    for (int i = 0; i < k; i++) {
        int gi = grassIdx[i];
        long long pos = p[gi];
        
        // 检查是否可以在草地位置放奶牛
        bool conflict = false;
        for (long long fp : f) {
            if (fp == pos) { conflict = true; break; }
        }
        
        if (!conflict) {
            extra[gi] = t[gi];
        }
    }
    
    // 排序取前n个
    sort(extra.begin(), extra.end(), greater<long long>());
    
    long long ans = 0;
    for (int i = 0; i < min(n, k); i++) {
        ans += extra[i];
    }
    
    cout << ans << "\n";
    return 0;
}
