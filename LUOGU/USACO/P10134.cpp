#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 300005;
int c[MAXN], result[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N, Q, C;
        cin >> N >> Q >> C;
        for (int i = 1; i <= N; i++) cin >> c[i];
        vector<pair<int,int>> pairs(Q);
        for (int j = 0; j < Q; j++) cin >> pairs[j].first >> pairs[j].second;
        sort(pairs.begin(), pairs.end());
        for (int i = 1; i <= N; i++) {
            if (c[i] != 0) result[i] = c[i];
            else result[i] = 1;
        }
        bool ok = true;
        for (int j = 0; j < Q && ok; j++) {
            int a = pairs[j].first, h = pairs[j].second;
            int mx = 0;
            for (int k = 1; k <= a; k++) mx = max(mx, result[k]);
            if (result[h] <= mx) result[h] = mx + 1;
            if (result[h] > C) { ok = false; break; }
            for (int k = a + 1; k < h; k++) {
                if (c[k] != 0 && c[k] > mx) { ok = false; break; }
                if (result[k] > mx) { ok = false; break; }
            }
        }
        if (!ok) { cout << -1 << "\n"; continue; }
        for (int i = 1; i <= N; i++) {
            if (i > 1) cout << " ";
            cout << result[i];
        }
        cout << "\n";
    }
    return 0;
}
