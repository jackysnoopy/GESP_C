#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x;
    cin >> x;

    if (x == 0) {
        cout << "1\n1\n";
        return 0;
    }

    int k = 1;
    while ((long long)k * (k - 1) / 2 < x) k++;

    set<int> avail;
    for (int i = 1; i <= k; i++) avail.insert(i);

    vector<int> ans;
    long long remaining = x;

    for (int i = 0; i < k; i++) {
        int n = k - i - 1;
        long long max_rest = (long long)n * (n - 1) / 2;

        int best = -1;
        for (int v : avail) {
            int less_than_v = 0;
            for (int u : avail) {
                if (u == v) break;
                less_than_v++;
            }
            if (less_than_v + max_rest >= remaining) {
                best = v;
                break;
            }
        }

        if (best == -1) best = *avail.rbegin();

        int less_than_v = 0;
        for (int u : avail) {
            if (u == best) break;
            less_than_v++;
        }

        ans.push_back(best);
        avail.erase(best);
        remaining -= less_than_v;
    }

    cout << k << "\n";
    for (int i = 0; i < k; i++) {
        if (i) cout << " ";
        cout << ans[i];
    }
    cout << "\n";
    return 0;
}
