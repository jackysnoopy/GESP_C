#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    
    vector<int> a(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        cin >> a[i];
    }
    
    // 记录每个数字的位置
    vector<int> pos(n + 1);
    for (int i = 0; i < 2 * n; i++) {
        pos[a[i]] = i;
    }
    
    // 简单贪心：每次选择最近的情侣
    int ans = 0;
    vector<bool> removed(2 * n, false);
    
    for (int i = 0; i < 2 * n; i++) {
        if (removed[i]) continue;
        
        int val = a[i];
        int partner_pos = pos[val];
        
        if (partner_pos == i + 1) {
            // 已经相邻
            removed[i] = true;
            removed[partner_pos] = true;
            ans++;
        } else {
            // 需要交换
            ans++;
            // 交换相邻位置
            for (int j = i + 1; j < partner_pos; j++) {
                if (!removed[j]) {
                    ans++;
                }
            }
            removed[i] = true;
            removed[partner_pos] = true;
        }
    }
    
    cout << ans << "\n";
    return 0;
}