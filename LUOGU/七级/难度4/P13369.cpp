#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int C, D;
        cin >> C >> D;

        vector<pair<int, int>> vendors;
        for (int i = 0; i < C; i++) {
            int p, v;
            cin >> p >> v;
            for (int j = 0; j < v; j++) vendors.push_back({p, 0});
        }

        sort(vendors.begin(), vendors.end());
        int n = vendors.size();

        vector<int> target(n);
        for (int i = 0; i < n; i++) target[i] = i * D;

        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, (long long)abs(vendors[i].first - target[i]));
        }

        cout << "Case #" << t << ": " << ans << "\n";
    }

    return 0;
}
