#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 2000005;
int n, k;
int a[MAXN];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    
    // 模拟状态变化
    vector<int> state(n + 1);
    for (int i = 1; i <= n; i++) {
        if (a[i] == 1) state[i] = 1;  // 恒卷
        else if (a[i] == 2) state[i] = 0;  // 恒颓
        else state[i] = -1;  // 暂人
    }
    
    // 尝试交换暂人
    int ans = 0;
    vector<int> temp_state = state;
    
    // 计算当前状态的卷数
    auto countRoll = [](vector<int>& s) {
        int cnt = 0;
        for (int i = 1; i < (int)s.size(); i++) {
            if (s[i] == 1) cnt++;
        }
        return cnt;
    };
    
    // 简单贪心：交换暂卷人和暂颓人
    vector<int> temp_a = a;
    for (int i = 1; i <= n && k > 0; i++) {
        if (temp_a[i] == 3) {  // 暂卷人
            for (int j = i + 1; j <= n && k > 0; j++) {
                if (temp_a[j] == 4) {  // 暂颓人
                    swap(temp_a[i], temp_a[j]);
                    k--;
                    break;
                }
            }
        }
    }
    
    // 模拟稳定状态
    vector<int> final_state(n + 1);
    for (int i = 1; i <= n; i++) {
        if (temp_a[i] == 1) final_state[i] = 1;
        else if (temp_a[i] == 2) final_state[i] = 0;
        else final_state[i] = -1;
    }
    
    // 计算稳定状态的卷数
    for (int iter = 0; iter < 100; iter++) {
        bool changed = false;
        vector<int> next_state = final_state;
        for (int i = 2; i < n; i++) {
            if (final_state[i] == -1) {
                int left = final_state[i-1];
                int right = final_state[i+1];
                if (temp_a[i] == 3) {  // 暂卷人：有卷则卷
                    if (left == 1 || right == 1) next_state[i] = 1;
                    else next_state[i] = 0;
                } else {  // 暂颓人：有颓则颓
                    if (left == 0 || right == 0) next_state[i] = 0;
                    else next_state[i] = 1;
                }
                if (next_state[i] != final_state[i]) changed = true;
            }
        }
        final_state = next_state;
        if (!changed) break;
    }
    
    ans = countRoll(final_state);
    printf("%d\n", ans);
    return 0;
}