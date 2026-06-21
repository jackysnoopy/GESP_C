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
        int n, k;
        cin >> n >> k;

        vector<pair<int, int>> items;
        for (int i = 0; i < n; i++) {
            int c, w, f;
            cin >> c >> w >> f;
            for (int j = 0; j < c; j++) {
                items.push_back({f, w});
            }
        }

        sort(items.begin(), items.end(), greater<pair<int, int>>());

        long long ans = 0;
        int idx = 0;

        while (idx < (int)items.size()) {
            int remaining = k;
            int max_floor = items[idx].first;

            while (idx < (int)items.size() && remaining >= items[idx].second) {
                remaining -= items[idx].second;
                idx++;
            }

            ans += max_floor;
        }

        cout << ans << "\n";
    }

    return 0;
}
