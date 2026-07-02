#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int K, N;
        cin >> K >> N;
        vector<long long> X(N), C(N);
        for (int i = 0; i < N; i++) cin >> X[i];
        for (int i = 0; i < N; i++) cin >> C[i];
        // Sort by position
        vector<int> idx(N);
        for (int i = 0; i < N; i++) idx[i] = i;
        sort(idx.begin(), idx.end(), [&](int a, int b) { return X[a] < X[b]; });
        vector<long long> sx(N), sc(N);
        for (int i = 0; i < N; i++) { sx[i] = X[idx[i]]; sc[i] = C[idx[i]]; }
        long long ans = 1e18;
        // Try each spot as warehouse
        for (int w = 0; w < N; w++) {
            // Cost of warehouse
            long long wh_cost = sc[w];
            // Compute stall costs for all other spots
            vector<long long> stall_cost;
            for (int i = 0; i < N; i++) {
                if (i == w) continue;
                stall_cost.push_back(sc[i] + abs(sx[w] - sx[i]));
            }
            // Select K smallest
            if ((int)stall_cost.size() < K) continue;
            nth_element(stall_cost.begin(), stall_cost.begin() + K, stall_cost.end());
            long long total = wh_cost;
            for (int i = 0; i < K; i++) total += stall_cost[i];
            ans = min(ans, total);
        }
        cout << "Case #" << t << ": " << ans << "\n";
    }
    return 0;
}
