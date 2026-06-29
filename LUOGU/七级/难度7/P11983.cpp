#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    cin >> N >> M;
    
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    
    vector<int> L(M), R(M);
    for (int i = 0; i < M; i++) {
        cin >> L[i] >> R[i];
        L[i]--;
        R[i]--;
    }
    
    // 展览会问题
    // 排列画作，使得杂志报道的吸引力字典序最大
    
    // 贪心：按影响力从大到小处理杂志
    vector<int> order(M);
    for (int i = 0; i < M; i++) order[i] = i;
    
    vector<int> result(M);
    vector<bool> used(N, false);
    
    for (int idx = 0; idx < M; idx++) {
        int j = order[idx];
        
        // 找到这个杂志覆盖区间内的最大美观值
        int max_val = 0;
        for (int k = L[j]; k <= R[j]; k++) {
            if (!used[k]) {
                max_val = max(max_val, A[k]);
            }
        }
        
        result[j] = max_val;
        
        // 标记使用过的画作
        for (int k = L[j]; k <= R[j]; k++) {
            if (A[k] == max_val && !used[k]) {
                used[k] = true;
                break;
            }
        }
    }
    
    for (int i = 0; i < M; i++) {
        cout << result[i] << "\n";
    }
    
    return 0;
}
