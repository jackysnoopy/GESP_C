#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
    }
    
    // 选区间问题
    // 对于每个区间，选择操作1(区间内+1)或操作2(区间外+1)
    // 使得最终数列最大值最小
    
    // 贪心策略：尽量选择操作使得重叠区域最小
    string ans(n, '0');
    int max_val = 0;
    
    // 计算每个位置被覆盖的次数
    vector<int> cnt(2 * n + 2, 0);
    for (int i = 0; i < n; i++) {
        if (ans[i] == '1') {
            cnt[l[i]]++;
            cnt[r[i] + 1]--;
        } else {
            cnt[1]++;
            cnt[l[i]]--;
            cnt[r[i] + 1]++;
        }
    }
    
    // 计算最大值
    int cur = 0;
    for (int i = 1; i <= 2 * n; i++) {
        cur += cnt[i];
        max_val = max(max_val, cur);
    }
    
    cout << max_val << "\n";
    cout << ans << "\n";
    
    return 0;
}
