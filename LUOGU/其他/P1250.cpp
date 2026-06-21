#include <iostream>
#include <algorithm>
using namespace std;
struct Req { int b, e, t; };
bool cmp(const Req& a, const Req& b) { return a.e < b.e || (a.e == b.e && a.b < b.b); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, h;
    cin >> n >> h;
    Req r[3001];
    for (int i = 0; i < h; i++) cin >> r[i].b >> r[i].e >> r[i].t;
    sort(r, r + h, cmp);
    bool tree[3001] = {};
    int ans = 0;
    for (int i = 0; i < h; i++) {
        int cnt = 0;
        for (int j = r[i].b; j <= r[i].e; j++) if (tree[j]) cnt++;
        int need = r[i].t - cnt;
        for (int j = r[i].e; j >= r[i].b && need > 0; j--) {
            if (!tree[j]) { tree[j] = true; need--; ans++; }
        }
    }
    cout << ans << "\n";
    return 0;
}
