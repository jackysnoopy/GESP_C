#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Beaver {
    int x, y, z;
};

int n;
Beaver b[150005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> b[i].x >> b[i].y >> b[i].z;
    }
    
    if (n < 3) {
        cout << -1 << "\n";
        return 0;
    }
    
    // Each member must have one ability strictly greater than the other two
    // Total ability = max(X) + max(Y) + max(Z)
    // Enumerate who is the "X expert", "Y expert", "Z expert"
    
    // Sort by each ability
    vector<int> idx_x(n), idx_y(n), idx_z(n);
    for (int i = 0; i < n; i++) idx_x[i] = idx_y[i] = idx_z[i] = i;
    
    sort(idx_x.begin(), idx_x.end(), [&](int i, int j) { return b[j].x < b[i].x; });
    sort(idx_y.begin(), idx_y.end(), [&](int i, int j) { return b[j].y < b[i].y; });
    sort(idx_z.begin(), idx_z.end(), [&](int i, int j) { return b[j].z < b[i].z; });
    
    long long ans = -1;
    
    for (int p = 0; p < 6; p++) {
        for (int i = 0; i < min(5, n); i++) {
            for (int j = 0; j < min(5, n); j++) {
                for (int k = 0; k < min(5, n); k++) {
                    int bi = idx_x[i]; // best X
                    int bj = idx_y[j]; // best Y
                    int bk = idx_z[k]; // best Z
                    
                    if (bi == bj || bi == bk || bj == bk) continue;
                    
                    // Check: bi must have X strictly > others' X
                    // bj must have Y strictly > others' Y
                    // bk must have Z strictly > others' Z
                    if (b[bi].x <= b[bj].x || b[bi].x <= b[bk].x) continue;
                    if (b[bj].y <= b[bi].y || b[bj].y <= b[bk].y) continue;
                    if (b[bk].z <= b[bi].z || b[bk].z <= b[bj].z) continue;
                    
                    long long total = (long long)max({b[bi].x, b[bj].x, b[bk].x}) +
                                      (long long)max({b[bi].y, b[bj].y, b[bk].y}) +
                                      (long long)max({b[bi].z, b[bj].z, b[bk].z});
                    ans = max(ans, total);
                }
            }
        }
    }
    
    cout << ans << "\n";
    return 0;
}
