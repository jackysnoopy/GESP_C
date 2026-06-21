#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, t, m;
        cin >> n >> t >> m;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        vector<int> cnt(n + 1, 0);
        for (int i = 0; i < m; i++) {
            int x;
            cin >> x;
            cnt[x]++;
        }
        vector<pair<int,int>> need;
        for (int i = 1; i <= n; i++) {
            int damage = cnt[i] * 2;
            int deficit = damage - a[i];
            if (deficit > 0) {
                need.push_back({deficit, i});
            }
        }
        sort(need.begin(), need.end());
        int saved = 0;
        int time_left = t;
        for (auto& p : need) {
            if (time_left >= p.first) {
                time_left -= p.first;
                saved++;
            } else {
                break;
            }
        }
        cout << (n - need.size()) + saved << "\n";
    }
    return 0;
}
