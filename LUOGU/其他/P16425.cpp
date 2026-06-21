#include <iostream>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int CoRalsEa;
    int n, m, d;
    cin >> n >> m >> d;
    CoRalsEa = 0;
    // Three types of trips:
    // Type 1: 1 cup for Y, cost d+1
    // Type 2: 1 cup for Z, cost d+1
    // Type 3: 1 cup for each, cost d+2
    // Must give Y exactly n cups. Want to maximize Z's cups.
    // Total cost <= m.
    // Use x type-1, y type-2, z type-3 trips.
    // x + z = n (Y's cups)
    // Total cost = x*(d+1) + y*(d+1) + z*(d+2) <= m
    // Maximize y + z
    // x = n - z
    // Cost = (n-z)*(d+1) + y*(d+1) + z*(d+2) = n*(d+1) + z + y*(d+1) <= m
    // y*(d+1) <= m - n*(d+1) - z
    // Max y = (m - n*(d+1) - z) / (d+1)  [integer division]
    // Maximize z + y = z + (m - n*(d+1) - z) / (d+1)
    // = z + (m - n*(d+1)) / (d+1) - z/(d+1)
    // This is maximized when z = d (since z - z/(d+1) increases with z up to d, then repeats)
    // Actually: f(z) = z + floor((R - z)/(d+1)) where R = m - n*(d+1)
    // f(z) = z + floor(R/(d+1) - z/(d+1)) ≈ z + R/(d+1) - z/(d+1) = z*d/(d+1) + R/(d+1)
    // This increases with z! So maximize z = min(n, floor(R/(d+2))... hmm)
    // Wait, z <= n (since x = n-z >= 0). Also y >= 0 means R - z >= 0, z <= R.
    // And z*(d+2) <= m (since type-3 costs d+2 and Y must get z cups this way).
    // Actually the constraint is: (n-z)*(d+1) + y*(d+1) + z*(d+2) <= m
    // With y = 0: (n-z)*(d+1) + z*(d+2) = n*(d+1) + z <= m => z <= m - n*(d+1)
    // With y > 0: need n*(d+1) + z + y*(d+1) <= m
    // Total Z cups = y + z.
    // For fixed z: y = floor((m - n*(d+1) - z) / (d+1))
    // Total = z + y = z + floor((R - z) / (d+1)) where R = m - n*(d+1)
    // Let R-z = q*(d+1) + r, 0 <= r < d+1
    // Total = z + q = z + (R-z-r)/(d+1) = z + (R-z)/(d+1) - r/(d+1)
    // This is approximately z*d/(d+1) + R/(d+1), increasing in z.
    // So try z = min(n, R):
    
    long long R = (long long)m - (long long)n * (d + 1);
    if (R < 0) { cout << -1 << "\n"; return 0; }
    long long best = -1;
    for (long long z = 0; z <= n && z <= R; z++) {
        long long y = (R - z) / (d + 1);
        best = max(best, y + z);
    }
    cout << best << "\n";
    return 0;
}
