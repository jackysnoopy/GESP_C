#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int C, D;
        long long V;
        cin >> C >> D >> V;

        vector<long long> denoms(D);
        for (int i = 0; i < D; i++) cin >> denoms[i];

        vector<bool> can(V + 1, false);
        can[0] = true;

        for (long long d : denoms) {
            for (long long v = V; v >= d; v--) {
                for (int c = 1; c <= C && c * d <= v; c++) {
                    if (can[v - c * d]) can[v] = true;
                }
            }
        }

        int ans = 0;
        for (long long v = 1; v <= V; v++) {
            if (!can[v]) {
                ans++;
                for (long long w = V; w >= v; w--) {
                    for (int c = 1; c <= C && c * v <= w; c++) {
                        if (can[w - c * v]) can[w] = true;
                    }
                }
            }
        }

        cout << "Case #" << t << ": " << ans << "\n";
    }

    return 0;
}
