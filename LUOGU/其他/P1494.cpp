#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
const int MAXN = 50001;
int a[MAXN], cnt[MAXN], sz;
struct Query { int l, r, id; };
bool cmp(const Query &a, const Query &b) {
    if (a.l / sz != b.l / sz) return a.l / sz < b.l / sz;
    return a.r < b.r;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<Query> q(m);
    for (int i = 0; i < m; ++i) { cin >> q[i].l >> q[i].r; q[i].id = i; }
    sz = (int)sqrt(n);
    sort(q.begin(), q.end(), cmp);
    vector<long long> num(m), den(m);
    int cl = 1, cr = 0;
    long long cur = 0;
    for (auto &qi : q) {
        int l = qi.l, r = qi.r;
        while (cr < r) { cr++; cur += cnt[a[cr]] * 2 + 1; cnt[a[cr]]++; }
        while (cl > l) { cl--; cur += cnt[a[cl]] * 2 + 1; cnt[a[cl]]++; }
        while (cr > r) { cnt[a[cr]]--; cur -= cnt[a[cr]] * 2 + 1; cr--; }
        while (cl < l) { cnt[a[cl]]--; cur -= cnt[a[cl]] * 2 + 1; cl++; }
        long long len = r - l + 1;
        num[qi.id] = cur - len;
        den[qi.id] = len * (len - 1);
    }
    for (int i = 0; i < m; ++i) {
        if (num[i] == 0) cout << "0/1\n";
        else { long long g = gcd(num[i], den[i]); cout << num[i]/g << "/" << den[i]/g << '\n'; }
    }
    return 0;
}
