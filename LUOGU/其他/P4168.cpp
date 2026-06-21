#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<int> b(a.begin() + 1, a.end());
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 1; i <= n; ++i) a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    int sz = (int)sqrt(n), bl = (n + sz - 1) / sz;
    vector<vector<int>> cnt(bl + 1, vector<int>(b.size(), 0));
    for (int i = 1; i <= n; ++i) cnt[(i - 1) / sz][a[i]]++;
    vector<vector<int>> pre(bl + 1, vector<int>(bl + 1, 0));
    for (int i = 0; i < bl; ++i) {
        vector<int> tmp(b.size(), 0);
        for (int j = i; j < bl; ++j) {
            pre[i][j] = pre[i][j - 1];
            int best = pre[i][j - 1] > 0 ? pre[i][j - 1] : -1;
            for (int k = j * sz; k < min((j + 1) * sz, n); ++k) tmp[a[k]]++;
            if (best < 0 || tmp[a[best]] < tmp[best]) best = best;
            for (int v = 0; v < (int)b.size(); ++v)
                if (tmp[v] > (best < 0 ? 0 : tmp[best]) || (tmp[v] == (best < 0 ? 0 : tmp[best]) && v < best)) best = v;
            pre[i][j] = best >= 0 ? b[best] : 0;
        }
    }
    int last = 0;
    while (m--) {
        int l, r; cin >> l >> r;
        l = (l + last - 1) % n + 1; r = (r + last - 1) % n + 1;
        if (l > r) swap(l, r);
        int bl2 = (l - 1) / sz, br2 = (r - 1) / sz;
        int ans = -1, ansCnt = 0;
        if (bl2 == br2) {
            vector<int> tmp(b.size(), 0);
            for (int i = l; i <= r; ++i) { tmp[a[i]]++; if (tmp[a[i]] > ansCnt || (tmp[a[i]] == ansCnt && a[i] < ans)) { ans = a[i]; ansCnt = tmp[a[i]]; } }
            ans = b[ans];
        } else {
            vector<int> tmp(b.size(), 0);
            for (int i = l; i < (bl2 + 1) * sz; ++i) tmp[a[i]]++;
            for (int i = br2 * sz; i <= r; ++i) tmp[a[i]]++;
            ansCnt = 0; ans = -1;
            for (int v = 0; v < (int)b.size(); ++v)
                if (tmp[v] > ansCnt || (tmp[v] == ansCnt && v < ans)) { ans = v; ansCnt = tmp[v]; }
            if (bl2 + 1 <= br2 - 1) {
                int midans = pre[bl2 + 1][br2 - 1];
                int midv = lower_bound(b.begin(), b.end(), midans) - b.begin();
                int midcnt = 0;
                for (int i = (bl2 + 1) * sz; i < (br2) * sz; ++i) if (a[i] == midv) midcnt++;
                midcnt += tmp[midv];
                if (midcnt > ansCnt || (midcnt == ansCnt && midv < ans)) { ans = midv; ansCnt = midcnt; }
            }
            ans = b[ans];
        }
        last = ans;
        cout << ans << '\n';
    }
    return 0;
}
