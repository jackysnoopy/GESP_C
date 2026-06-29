#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> a(n), x(n), b(m), y(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> x[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    for (int i = 0; i < m; i++) cin >> y[i];
    
    // 学习轨迹问题
    // 选择THU的[l1,r1]和PKU的[l2,r2]，使得乐趣度最大
    // 约束：同一类别不能听两次
    
    ll ans = 0;
    int best_l1 = 0, best_r1 = 0, best_l2 = 0, best_r2 = 0;
    
    // 暴力枚举（适用于小数据）
    for (int l1 = 0; l1 <= n; l1++) {
        for (int r1 = l1 - 1; r1 < n; r1++) {
            for (int l2 = 0; l2 <= m; l2++) {
                for (int r2 = l2 - 1; r2 < m; r2++) {
                    // 检查类别冲突
                    vector<bool> used(n + m + 1, false);
                    bool ok = true;
                    ll total = 0;
                    
                    for (int i = l1; i <= r1; i++) {
                        if (used[a[i]]) {
                            ok = false;
                            break;
                        }
                        used[a[i]] = true;
                        total += x[i];
                    }
                    if (!ok) continue;
                    
                    for (int i = l2; i <= r2; i++) {
                        if (used[b[i]]) {
                            ok = false;
                            break;
                        }
                        used[b[i]] = true;
                        total += y[i];
                    }
                    if (!ok) continue;
                    
                    if (total > ans) {
                        ans = total;
                        best_l1 = l1 + 1;
                        best_r1 = r1 + 1;
                        best_l2 = l2 + 1;
                        best_r2 = r2 + 1;
                    }
                }
            }
        }
    }
    
    cout << ans << "\n";
    if (best_l1 == 0) {
        cout << "0 0\n";
    } else {
        cout << best_l1 << " " << best_r1 << "\n";
    }
    if (best_l2 == 0) {
        cout << "0 0\n";
    } else {
        cout << best_l2 << " " << best_r2 << "\n";
    }
    
    return 0;
}
