#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long m, d;
    int n;
    cin >> m >> d >> n;
    vector<long long> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    sort(x.rbegin(), x.rend());
    // First: need to reach the taxi base at distance d
    if (d > x[0]) { cout << "-1\n"; return 0; }
    long long fuel = x[0] - d; // fuel left after reaching base
    int cnt = 1;
    long long pos = 0; // position relative to base (0 = at base)
    // After first taxi, we're at position 0 with 'fuel' gas
    // Remaining distance: m - d
    // Use remaining taxis greedily
    int idx = 1;
    while (fuel < m - d) {
        if (idx >= n) { cout << "-1\n"; return 0; }
        // Each subsequent taxi: go back from current position to pick up
        // Actually, taxis are all at the base. We can walk back.
        // Walk back min(fuel, pos) to pick up taxi, then drive forward.
        // Actually simpler: we have fuel. We need to cover m-d total.
        // Pick the next taxi. Its range is x[idx]. We're at position 'pos'.
        // We can use this taxi to advance.
        long long range = x[idx];
        // The taxi can cover from -(range) to range from the base.
        // But we're at position 'pos' with 'fuel' gas.
        // We walk back to base (cost: pos), then drive forward range.
        // Or: drive back from pos using fuel, pick up taxi, drive forward.
        
        // Actually: we drive back to base using fuel, then use next taxi.
        // Cost to get back to base from pos: min(pos, fuel). 
        // But we can drive backwards too.
        fuel -= pos; // drive back to base
        if (fuel < 0) { cout << "-1\n"; return 0; }
        fuel = x[idx]; // new taxi
        cnt++;
        idx++;
    }
    cout << cnt << "\n";
    return 0;
}
