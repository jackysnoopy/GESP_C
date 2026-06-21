#include <iostream>
#include <vector>
using namespace std;
int fa[1000001], rnk[1000001];
int find(int x) { return fa[x]==x ? x : fa[x]=find(fa[x]); }
bool unite(int x, int y) {
    x=find(x); y=find(y);
    if (x==y) return false;
    if (rnk[x]<rnk[y]) swap(x,y);
    fa[y]=x;
    if (rnk[x]==rnk[y]) rnk[x]++;
    return true;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) { fa[i]=i; rnk[i]=0; }
    int cnt = 0;
    vector<pair<int,int>> removed;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (u <= k && v <= k) {
            removed.push_back({u,v});
        } else if (u <= k || v <= k) {
            if (!unite(u,v)) removed.push_back({u,v});
        } else {
            if (!unite(u,v)) removed.push_back({u,v});
        }
    }
    cout << removed.size() << "\n";
    for (auto& p : removed) {
        if (p.first > p.second) swap(p.first, p.second);
        cout << p.first << " " << p.second << "\n";
    }
    return 0;
}
