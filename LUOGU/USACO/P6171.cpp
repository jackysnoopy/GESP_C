#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int fa[62501];
int find(int x) { return fa[x]==x?x:fa[x]=find(fa[x]); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int A, B, n, m;
    cin >> A >> B >> n >> m;
    vector<int> va(n), vb(m);
    for (int i = 0; i < n; i++) cin >> va[i];
    for (int i = 0; i < m; i++) cin >> vb[i];
    va.push_back(0); va.push_back(A);
    vb.push_back(0); vb.push_back(B);
    sort(va.begin(), va.end());
    sort(vb.begin(), vb.end());
    // MST on (n+1)*(m+1) grid
    // Edges: horizontal and vertical
    vector<pair<int,pair<int,int>>> edges;
    int N = n+1, M = m+1;
    // Horizontal edges (between columns)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M-1; j++)
            edges.push_back({vb[j+1]-vb[j], {i*M+j, i*M+j+1}});
    // Vertical edges (between rows)
    for (int i = 0; i < N-1; i++)
        for (int j = 0; j < M; j++)
            edges.push_back({va[i+1]-va[i], {i*M+j, (i+1)*M+j}});
    sort(edges.begin(), edges.end());
    for (int i = 0; i < N*M; i++) fa[i] = i;
    long long ans = 0;
    for (auto& e : edges) {
        int fu = find(e.second.first), fv = find(e.second.second);
        if (fu != fv) {
            fa[fu] = fv;
            ans += e.first;
        }
    }
    cout << ans << "\n";
    return 0;
}
