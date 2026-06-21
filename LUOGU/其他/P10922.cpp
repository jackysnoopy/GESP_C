#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        sort(a.begin(), a.end());
        // Brute force for small n
        if (n <= 8) {
            int best = 0;
            do {
                vector<int> cur = a;
                int cnt = 0;
                int h = 1;
                while (h <= (int)cur.size()) {
                    int val = cur[h - 1];
                    cnt++;
                    cur.erase(cur.begin() + h - 1);
                    h = val;
                }
                best = max(best, cnt);
            } while (next_permutation(a.begin(), a.end()));
            cout << best << "\n";
        } else {
            // Greedy: try to maximize chain length
            // Strategy: place values to make the chain visit all positions
            // Simple heuristic: sort and simulate
            vector<int> cur = a;
            int cnt = 0;
            int h = 1;
            while (h <= (int)cur.size()) {
                int val = cur[h - 1];
                cnt++;
                cur.erase(cur.begin() + h - 1);
                h = val;
            }
            cout << cnt << "\n";
        }
    }
    return 0;
}
