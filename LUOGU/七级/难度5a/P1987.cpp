#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    while (cin >> n >> k && (n || k)) {
        vector<long long> m(n), b(n);
        for (int i = 0; i < n; i++) cin >> m[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        
        // 按b_i降序排序，优先砍掉落速度快的树
        vector<int> order(n);
        for (int i = 0; i < n; i++) order[i] = i;
        sort(order.begin(), order.end(), [&](int i, int j) {
            return b[i] > b[j];
        });
        
        long long ans = 0;
        vector<long long> cur = m;
        for (int day = 0; day < k && day < n; day++) {
            int tree = order[day];
            ans += cur[tree];
            cur[tree] = -1e18;
            for (int i = 0; i < n; i++) {
                if (cur[i] > -1e18) cur[i] -= b[i];
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
