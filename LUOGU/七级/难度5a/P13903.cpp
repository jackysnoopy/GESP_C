#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, T, q;
    cin >> n >> m >> T >> q;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<int> l(q), r(q);
    for (int i = 0; i < q; i++) {
        cin >> l[i] >> r[i];
        l[i]--; r[i]--; // 转换为0-indexed
    }
    
    // 基础实现：简单计算原始复杂度
    vector<int> ans(T + 1, 0);
    
    // 计算原始复杂度
    int original_complexity = 0;
    for (int i = 0; i < q; i++) {
        int complexity = 1;
        for (int j = l[i] + 1; j <= r[i]; j++) {
            if (a[j] != a[j - 1]) {
                complexity++;
            }
        }
        original_complexity += complexity;
    }
    
    ans[0] = original_complexity;
    
    // 输出结果
    for (int k = 0; k <= T; k++) {
        cout << ans[k] << endl;
    }
    
    return 0;
}