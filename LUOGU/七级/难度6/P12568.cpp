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
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // 检查是否已经所有元素不同
    vector<int> sorted_a = a;
    sort(sorted_a.begin(), sorted_a.end());
    bool all_different = true;
    for (int i = 1; i < n; i++) {
        if (sorted_a[i] == sorted_a[i - 1]) {
            all_different = false;
            break;
        }
    }
    
    if (all_different) {
        cout << 0 << endl;
        return 0;
    }
    
    // 统计重复元素
    vector<int> freq(100001, 0);
    int max_freq = 0;
    for (int x : a) {
        freq[x]++;
        max_freq = max(max_freq, freq[x]);
    }
    
    // 简化策略：每次操作可以处理一个连续子数组
    // 最优策略需要更复杂的分析
    
    // 启发式：至少需要 max_freq - 1 次操作
    cout << max_freq - 1 << endl;
    
    return 0;
}
