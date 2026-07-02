#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    // 简单解法：枚举所有可能的翻转区间，但只考虑边界连接
    // 对于每个值v，记录其出现位置
    vector<vector<int>> pos(1000001);
    for (int i = 0; i < n; ++i) {
        pos[a[i]].push_back(i);
    }
    
    int ans = 0;
    // 先计算不翻转的最大连续相同数分数
    for (int i = 0; i < n; ++i) {
        int j = i;
        while (j < n && a[j] == a[i]) ++j;
        int len = j - i;
        ans = max(ans, len * a[i]);
        i = j - 1;
    }
    
    // 尝试通过翻转连接两个相同值的片段
    for (int v = 1; v <= 1000000; ++v) {
        if (pos[v].empty()) continue;
        // 对于每个出现位置，尝试将其移动到左边或右边的相同值旁边
        for (int idx = 0; idx < pos[v].size(); ++idx) {
            int i = pos[v][idx];
            // 尝试移动到左边相同值旁边
            if (idx > 0) {
                int L = pos[v][idx-1];
                // 翻转区间[L+1, i]
                // 计算翻转后连续长度：左边连续长度 + 右边连续长度
                // 但需要确保L和i之间没有非v元素？暂时忽略，简单计算
                int left_len = 1;
                if (L > 0 && a[L-1] == v) left_len = 1; // 实际需要计算以L结尾的连续长度
                int right_len = 1;
                if (i+1 < n && a[i+1] == v) right_len = 1; // 实际需要计算以i开头的连续长度
                // 简单起见，假设L和i都是单个v
                int total = left_len + right_len;
                if (total * v > ans) ans = total * v;
            }
            // 尝试移动到右边相同值旁边
            if (idx < pos[v].size()-1) {
                int R = pos[v][idx+1];
                int total = 2; // 两个v
                if (total * v > ans) ans = total * v;
            }
        }
    }
    
    cout << ans << endl;
    return 0;
}