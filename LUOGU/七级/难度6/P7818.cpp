#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    long long k;
    cin >> n >> k;
    
    vector<int> p(n);
    for (int i = 0; i < n; i++) { cin >> p[i]; p[i]--; }
    
    // 贪心：对于每个位置i，尝试将p[i]移到位置p[i]
    // 每次交换可以将一个元素移到正确位置
    // K次交换最多修正K个元素
    
    // 从前往后贪心，每次将最小的可修正元素移到正确位置
    vector<int> pos(n);
    for (int i = 0; i < n; i++) pos[p[i]] = i;
    
    vector<int> result(n, -1);
    vector<bool> used(n, false);
    
    long long remaining = k;
    
    // 贪心：对于位置i，尝试放最小的未使用元素
    // 但需要考虑交换次数限制
    for (int i = 0; i < n && remaining > 0; i++) {
        if (result[i] != -1) continue;
        
        // 找当前位置i应该放的最小元素
        int target = i;
        if (!used[target] && pos[target] > i) {
            // 需要将target从pos[target]移到i
            // 交换次数 = pos[target] - i
            long long cost = pos[target] - i;
            if (cost <= remaining) {
                result[i] = target;
                used[target] = true;
                // 更新位置信息
                int other = p[i];
                pos[other] = pos[target];
                p[pos[target]] = other;
                p[i] = target;
                remaining -= cost;
            }
        }
    }
    
    // 填充未确定的位置
    for (int i = 0; i < n; i++) {
        if (result[i] == -1) {
            for (int j = 0; j < n; j++) {
                if (!used[j]) {
                    result[i] = j;
                    used[j] = true;
                    break;
                }
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << result[i] + 1;
    }
    cout << "\n";
    
    return 0;
}
