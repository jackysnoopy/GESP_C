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
        int n, m;
        cin >> n >> m;

        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        vector<pair<long long, int>> stations(m);
        for (int i = 0; i < m; i++) cin >> stations[i].first >> stations[i].second;

        sort(stations.begin(), stations.end());

        long long total_energy = 0;
        for (int i = 0; i < n; i++) total_energy += a[i];

        long long max_dist = total_energy;
        int station_idx = 0;

        for (int i = 0; i < n; i++) {
            while (station_idx < m && stations[station_idx].first <= max_dist) {
                int t = stations[station_idx].second - 1;
                a[t] += 1;
                total_energy += 1;
                max_dist = total_energy;
                station_idx++;
            }
        }

        cout << max_dist << "\n";
    }

    return 0;
}
