#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    int m, k;
    cin >> n >> m >> k;
    vector<vector<long long>> bonus(m + 1);
    for (int i = 0; i < k; i++) {
        int p;
        long long q;
        cin >> p >> q;
        bonus[p].push_back(q);
    }
    vector<long long> steps(m + 1, 0);
    for (int i = 1; i <= m; i++) {
        sort(bonus[i].rbegin(), bonus[i].rend());
        steps[i] = bonus[i].empty() ? 0 : bonus[i][0];
    }
    long long total = 0;
    for (int i = 1; i <= m; i++) total += steps[i];
    if (total <= n) {
        long long ans = 0;
        for (int i = 1; i <= m; i++) {
            for (long long q : bonus[i]) {
                if (steps[i] >= q) {
                    long long t = steps[i] - q + 1;
                    ans += (steps[i] + t) * (steps[i] - t + 1) / 2;
                    break;
                }
            }
            if (bonus[i].empty() && steps[i] == 0) continue;
        }
        cout << ans << "\n";
        return 0;
    }
    cout << "0\n";
    return 0;
}
