#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long d;
    cin >> n >> d;
    vector<long long> v(n), c(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    for (int i = 0; i < n; i++) cin >> c[i];
    // At each station, can buy fuel at cost c[i] per unit.
    // Need d fuel per unit distance.
    // Greedy: at each station, buy fuel if it's cheap, but limited by tank.
    // Actually: we can buy any amount at any station.
    // Total fuel needed = d * (sum of distances) = d * v[n-1] (since v is positions).
    // Wait, v[i] is the price? Or distance? Let me re-read.
    // "v_i 表示每公里需要消耗的油量" - v[i] is fuel consumption per km at station i?
    // Actually from the data: n stations, v[i] = fuel consumption rate at station i?
    // No, re-reading: "公路上有n个站点", "v_i 表示每公里需要消耗的油量"
    // Hmm the data format isn't clear. Let me just implement a simple solution.
    // Actually: v[i] might be the distance between consecutive stations.
    // And c[i] is the price per unit fuel at station i.
    // We need to buy fuel to travel. Minimize cost.
    // Greedy: at each station, buy fuel if price is lower than any future station.
    
    // Simple greedy: at each station, buy enough to reach the next cheaper station.
    long long ans = 0;
    long long fuel = 0;
    for (int i = 0; i < n - 1; i++) {
        long long need = v[i] * d;
        if (fuel >= need) {
            fuel -= need;
        } else {
            long long buy = need - fuel;
            ans += buy * c[i];
            fuel = 0;
        }
        // Buy more if next station is more expensive
        if (i + 1 < n && c[i] <= c[i+1]) {
            // Buy enough to reach next cheaper station or end
            long long totalNeed = 0;
            int j = i + 1;
            while (j < n - 1 && c[j] >= c[i]) {
                totalNeed += v[j] * d;
                j++;
            }
            long long buyMore = min(totalNeed, (long long)1e18);
            ans += buyMore * c[i];
            fuel += buyMore - (j > i+1 ? 0 : 0);
        }
    }
    cout << ans << "\n";
    return 0;
}
