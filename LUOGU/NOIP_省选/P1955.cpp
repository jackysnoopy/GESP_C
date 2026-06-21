#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int fa[2000001], rk[2000001];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void merge(int a, int b) { a=find(a); b=find(b); if(a!=b) { if(rk[a]<rk[b]) swap(a,b); fa[b]=a; if(rk[a]==rk[b]) rk[a]++; } }
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> vals;
        vector<tuple<int,int,int>> cons;
        for (int i = 0; i < n; ++i) {
            int a,b,t; cin >> a >> b >> t;
            vals.push_back(a); vals.push_back(b);
            cons.push_back({a,b,t});
        }
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        auto getId = [&](int x) { return lower_bound(vals.begin(), vals.end(), x) - vals.begin(); };
        int m = vals.size();
        for (int i = 0; i < m; ++i) { fa[i] = i; rk[i] = 0; }
        bool ok = true;
        for (auto &c : cons) {
            int a,b,t; tie(a,b,t) = c;
            a = getId(a); b = getId(b);
            if (t == 1) merge(a, b);
        }
        for (auto &c : cons) {
            int a,b,t; tie(a,b,t) = c;
            a = getId(a); b = getId(b);
            if (t == 0 && find(a) == find(b)) { ok = false; break; }
        }
        cout << (ok ? "YES" : "NO") << '\n';
    }
    return 0;
}
