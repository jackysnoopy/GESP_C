#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K, N, C;
    cin >> K >> N >> C;

    vector<tuple<int, int, int>> groups(K);
    for (int i = 0; i < K; i++) {
        int s, e, m;
        cin >> s >> e >> m;
        groups[i] = {e, s, m};
    }

    sort(groups.begin(), groups.end());

    vector<int> diff(N + 2, 0);
    int ans = 0;

    for (int i = 0; i < K; i++) {
        int e = get<0>(groups[i]);
        int s = get<1>(groups[i]);
        int m = get<2>(groups[i]);
        int maxLoad = 0;
        int cur = 0;
        for (int j = 1; j <= e; j++) {
            cur += diff[j];
            if (j >= s && j < e) {
                maxLoad = max(maxLoad, cur);
            }
        }
        int can = min(m, C - maxLoad);
        ans += can;
        diff[s] += can;
        diff[e] -= can;
    }

    cout << ans << "\n";
    return 0;
}
