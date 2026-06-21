#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    string f;
    cin >> f;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> bad;
    for (int i = 0; i < m; ++i) if (f[i] == '1') bad.push_back(i + 1);
    if (bad.empty()) {
        cout << 0 << '\n';
        return 0;
    }
    int need = (int)bad.size();
    vector<int> cur = bad;
    int ans = 0;
    while (!cur.empty()) {
        ++ans;
        int last = cur.back();
        cur.clear();
        int nxt = last - 1;
        for (int i = (int)a.size() - 1; i >= 0; --i) {
            if (a[i] == last) {
                a.erase(a.begin() + i);
                break;
            }
        }
        while (nxt >= 1 && f[nxt - 1] == '1') {
            cur.push_back(nxt);
            --nxt;
        }
    }
    cout << ans << '\n';
    return 0;
}
