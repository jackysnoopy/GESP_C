#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<int> V(m);
        for (int i = 0; i < m; i++) cin >> V[i];
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        vector<int> cur(m, 0);
        int wasted = 0;
        for (int i = 0; i < n; i++) {
            int idx = a[i] - 1;
            if (cur[idx] < V[idx]) {
                cur[idx]++;
            } else if (idx + 1 < m && cur[idx + 1] < V[idx + 1]) {
                cur[idx + 1]++;
            } else {
                wasted++;
            }
        }
        cout << wasted << "\n";
    }
    return 0;
}
