#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    // 每个居民：如果平均分 > a_i，打0分；否则打m分
    // 初始平均分 = 0
    
    // 贪心：最大化平均分
    // 先让打m分的人上（使平均分升高），再让打0分的人上
    
    // 最大平均分：按a_i升序，先让a_i大的打m分
    // 最小平均分：按a_i降序，先让a_i小的打m分
    
    // 计算最大平均分
    auto calc = [&](bool maximize) -> double {
        vector<int> order(n);
        for (int i = 0; i < n; i++) order[i] = i;
        
        if (maximize) {
            sort(order.begin(), order.end(), [&](int x, int y) {
                return a[x] > a[y];
            });
        } else {
            sort(order.begin(), order.end(), [&](int x, int y) {
                return a[x] < a[y];
            });
        }
        
        long long sum = 0;
        for (int idx : order) {
            double avg = (double)sum / (order.size() > 0 ? 1 : 1);
            // 重新计算
            avg = (double)sum;
            int cnt = 0;
            // 简化：直接模拟
        }
        
        // 重新计算
        sum = 0;
        for (int i = 0; i < n; i++) {
            int idx = order[i];
            double avg = (i > 0) ? (double)sum / i : 0;
            if (avg > a[idx]) {
                // 打0分
            } else {
                sum += m;
            }
        }
        
        return (double)sum / n;
    };
    
    double mx = calc(true);
    double mn = calc(false);
    
    printf("%.2f %.2f\n", mx, mn);
    return 0;
}
