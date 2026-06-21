#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<ll> x(N), y(N);
    for (int i = 0; i < N; i++) cin >> x[i];
    for (int i = 0; i < N; i++) cin >> y[i];
    ll total_users = 0, total_spots = 0;
    for (int i = 0; i < N; i++) { total_users += y[i]; total_spots += x[i]; }
    if (total_users > total_spots) { cout << -1 << "\n"; return 0; }
    vector<ll> spots_avail(N);
    for (int i = 0; i < N; i++) spots_avail[i] = x[i];
    ll score = 0;
    for (int s = N - 1; s >= 0; s--) {
        ll remaining = y[s];
        for (int t = 0; t < s && remaining > 0; t++) {
            ll take = min(remaining, spots_avail[t]);
            spots_avail[t] -= take;
            remaining -= take;
            score += take;
        }
        if (remaining > 0) {
            ll take = min(remaining, spots_avail[s]);
            spots_avail[s] -= take;
            remaining -= take;
        }
        for (int t = s + 1; t < N && remaining > 0; t++) {
            ll take = min(remaining, spots_avail[t]);
            spots_avail[t] -= take;
            remaining -= take;
            score -= take;
        }
    }
    cout << score << "\n";
    return 0;
}
