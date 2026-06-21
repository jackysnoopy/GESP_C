#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<long long> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    // CS2 trade system: maximize profit, no loss items.
    // Each item has buy price v[i], and m days of prices w[i][j].
    // Sell item i on best day. Only sell if profit > 0.
    // If no profitable day, keep item (not counted).
    
    long long totalProfit = 0;
    for (int i = 0; i < n; i++) {
        long long bestPrice = 0;
        for (int j = 0; j < m; j++) {
            long long w;
            cin >> w;
            bestPrice = max(bestPrice, w);
        }
        if (bestPrice > v[i]) {
            totalProfit += bestPrice - v[i];
        }
    }
    cout << totalProfit << endl;
    return 0;
}
