#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    int wins = 0, losses = 0;
    vector<int> lossCosts, tieCosts;
    for (int i = 0; i < n; i++) {
        if (a[i] > b[i]) wins++;
        else if (a[i] < b[i]) { losses++; lossCosts.push_back(b[i] - a[i] + 1); }
        else tieCosts.push_back(1);
    }
    sort(lossCosts.begin(), lossCosts.end());
    sort(tieCosts.begin(), tieCosts.end());
    // Prefix sums
    vector<long long> lp(lossCosts.size() + 1, 0), tp(tieCosts.size() + 1, 0);
    for (int i = 0; i < (int)lossCosts.size(); i++) lp[i+1] = lp[i] + lossCosts[i];
    for (int i = 0; i < (int)tieCosts.size(); i++) tp[i+1] = tp[i] + tieCosts[i];
    long long ans = 1e18;
    for (int k1 = 0; k1 <= losses; k1++) {
        int need = losses - wins - 2 * k1 + 1;
        if (need < 0) need = 0;
        if (need > (int)tieCosts.size()) continue;
        long long cost = lp[k1] + tp[need];
        if (cost < ans) ans = cost;
    }
    cout << ans << "\n";
    return 0;
}
