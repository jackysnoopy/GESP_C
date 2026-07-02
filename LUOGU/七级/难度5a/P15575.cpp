#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> x(n), y(n);
        for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
        map<int, int> cnt;
        for (int i = 0; i < n; i++) cnt[x[i]]++;
        vector<int> xs;
        for (auto& p : cnt) xs.push_back(p.first);
        bool ok = true;
        int rem = 0;
        for (int i = 0; i < (int)xs.size(); i++) {
            int c = cnt[xs[i]];
            int cur = c + rem;
            if (i + 1 < (int)xs.size() && xs[i+1] == xs[i] + 1) {
                rem = cur % 2;
            } else {
                if (cur % 2 != 0) { ok = false; break; }
                rem = 0;
            }
        }
        if (rem > 0) ok = false;
        cout << (ok ? "YES" : "NO") << "\n";
    }
    return 0;
}
