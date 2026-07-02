#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
vector<pair<int, int>> adj[MAXN];
long long dist[MAXN];
int parent[MAXN];
int n;

void dfs(int u, int p) {
    parent[u] = p;
    for (int i = 0; i < (int)adj[u].size(); i++) {
        int v = adj[u][i].first, w = adj[u][i].second;
        if (v == p) continue;
        dist[v] = dist[u] + w;
        dfs(v, u);
    }
}

int farthest(int start) {
    for (int i = 1; i <= n; i++) dist[i] = -1;
    dist[start] = 0;
    dfs(start, -1);
    int mx = start;
    for (int i = 1; i <= n; i++)
        if (dist[i] > dist[mx]) mx = i;
    return mx;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    // Find tree diameter endpoints
    int a = farthest(1);
    int b = farthest(a);
    // Now dist[] from a gives distances from a
    // Run DFS from b to get distances from b
    for (int i = 1; i <= n; i++) dist[i] = -1;
    dist[b] = 0;
    dfs(b, -1);
    // The answer is related to the diameter
    // Worst case: parents look at two nodes that are far apart
    // The answer is max over all nodes v of:
    //   max(dist_a[v], dist_b[v]) + min(dist_a[v], dist_b[v]) / 2
    // Actually the answer is: for the tree diameter endpoints a, b with length D,
    // the worst case cost is D + max(dist_a[c] - dist_b[c]) / 2 ... 
    // Actually let me reconsider.
    // 
    // The problem: Chris is at some node C (unknown to teacher).
    // Parents know A, B, C. They go to closer of A,B first.
    // Teacher doesn't know A,B,C but wants worst case.
    // 
    // The worst case is when A and B are chosen adversarially.
    // For a fixed C, the worst case cost = max over choices of A,B of:
    //   min(d(C,A)+d(A,B), d(C,B)+d(B,A)) = d(C,A)+d(A,B) if d(C,A)<=d(C,B)
    // Actually: cost = min(d(C,A), d(C,B)) + d(A,B)
    // Worst case over A,B: max_{A,B} [min(d(C,A),d(C,B)) + d(A,B)]
    // = max_{A,B} [d(A,B) + min(d(C,A), d(C,B))]
    // 
    // This equals: for the diameter path a-b, the worst case for any C is:
    // D (the diameter length) ... actually it's more nuanced.
    //
    // For any C, the worst A,B are the two diameter endpoints.
    // cost = d(A,B) + min(d(C,A), d(C,B)) = D + min(d(C,A), d(C,B))
    // To maximize over C: choose C to maximize min(d(C,A), d(C,B))
    // This is maximized at the midpoint of the diameter path.
    // max min(d(C,A), d(C,B)) = D/2 (for even D) or (D-1)/2 (for odd)
    // 
    // Wait, but the problem says A and B are fixed (Shermie and Yashiro),
    // and C is also fixed. The teacher wants the worst case over all possible
    // A, B, C placements.
    //
    // Actually re-reading: the teacher doesn't know A, B, C.
    // The teacher wants: worst case over all (A, B, C) of the parents' cost.
    //
    // For fixed A, B, C: cost = d(C, closer(A,B)) + d(A,B)
    // = d(C,A) + d(A,B) if d(C,A) <= d(C,B)
    // = d(C,B) + d(A,B) if d(C,B) <= d(C,A)
    //
    // Worst case over A,B for fixed C:
    // Choose A,B to maximize min(d(C,A)+d(A,B), d(C,B)+d(A,B))
    // = max_{A,B} [d(A,B) + min(d(C,A), d(C,B))]
    //
    // For the diameter endpoints a,b:
    // d(a,b) + min(d(C,a), d(C,b)) is always >= any other choice of A,B
    // because d(a,b) is maximized.
    //
    // So worst case for fixed C = D + min(d(C,a), d(C,b))
    // where D = d(a,b) is the diameter.
    //
    // Now maximize over C: max_C [D + min(d(C,a), d(C,b))]
    // = D + max_C min(d(C,a), d(C,b))
    // max_C min(d(C,a), d(C,b)) = D/2 (the midpoint of the diameter path)
    //
    // But we need integer answer. Let's compute carefully.
    // Actually the answer is: D + max_C min(d(C,a), d(C,b))
    // For any node C on the diameter path from a to b at distance x from a:
    // min(d(C,a), d(C,b)) = min(x, D-x), maximized at x = D/2, value = D/2
    //
    // But C doesn't have to be on the diameter path. However, for any C,
    // min(d(C,a), d(C,b)) <= D/2 by triangle inequality (d(C,a)+d(C,b) >= D).
    //
    // So the answer is D + D/2? That doesn't match the sample.
    // Sample: D = 3 (path 1-2-3-4, diameter = 3)
    // Answer should be 4. D + D/2 = 3 + 1.5 = 4.5? No.
    //
    // Let me re-read the problem more carefully.
    // "如果 A 距离 C 比 B 距离 C 近，那么 Chris 的父母先去 Shermie 家寻找 Chris，
    //  如果找不到，Chris 的父母再去 Yashiro 家"
    // So: first go to closer of A,B, then go to the other.
    // Cost = d(C, closer) + d(closer, farther)
    // = min(d(C,A), d(C,B)) + d(A,B)
    //
    // For sample: tree 1-2-3-4, all edges weight 1. D = 3.
    // If A=1, B=4, C=2: cost = min(1,2) + 3 = 1+3 = 4. ✓
    // If A=1, B=4, C=3: cost = min(2,1) + 3 = 1+3 = 4.
    // If A=1, B=4, C=1: cost = min(0,3) + 3 = 0+3 = 3.
    // If A=2, B=4, C=1: cost = min(1,3) + 2 = 1+2 = 3.
    //
    // Worst case for C: max_C min(d(C,A), d(C,B)) + d(A,B)
    // For A=1, B=4: max_C min(d(C,1), d(C,4)) + 3
    // C=2: min(1,2)+3=4, C=3: min(2,1)+3=4. Max = 4. ✓
    //
    // Now worst over A,B: we need to check if other A,B give higher cost.
    // A=1, B=3: d(A,B)=2. max_C min(d(C,1),d(C,3))+2. C=2: min(1,1)+2=3. C=4: min(3,1)+2=3. Max=3.
    // A=2, B=4: d=2. C=1: min(1,3)+2=3. C=3: min(1,1)+2=3. Max=3.
    // A=1, B=2: d=1. Max is small.
    // So diameter endpoints give the worst case. Answer = 4. ✓
    //
    // General formula: answer = D + floor(D/2) = D + D/2 when D is integer
    // For D=3: 3+1=4. For D=4: 4+2=6. For D=5: 5+2=7.
    // Wait: max_C min(d(C,a), d(C,b)) where a,b are diameter endpoints.
    // This is the "radius" from the diameter midpoint = ceil(D/2)? No, floor(D/2).
    // For D=3: floor(3/2)=1. Answer = 3+1=4. ✓
    // For D=4: floor(4/2)=2. Answer = 4+2=6.
    //
    // So answer = D + D/2 = 3D/2? No, D + floor(D/2).
    // Actually it's just the diameter + radius = D + ceil(D/2)?
    // For D=3: 3+2=5? No that's wrong.
    // 
    // Hmm, let me think again. max_C min(d(C,a), d(C,b)):
    // C on the a-b path at position x from a: min(x, D-x)
    // Maximum is at x=D/2, value = D/2.
    // For D=3: max is 1 (at x=1 or x=2). Answer = 3+1=4. ✓
    // For D=5: max is 2 (at x=2 or x=3). Answer = 5+2=7.
    // For D=4: max is 2 (at x=2). Answer = 4+2=6.
    //
    // So answer = D + D/2 = 3D/2 for even D, D + (D-1)/2 = (3D-1)/2 for odd D.
    // Actually answer = D + floor(D/2).

    // Recompute: first find diameter
    int u = farthest(1);
    int v = farthest(u);
    long long D = dist[v];

    // Now find max_C min(d(C,u), d(C,v))
    // dist from u:
    for (int i = 1; i <= n; i++) dist[i] = -1;
    dist[u] = 0;
    dfs(u, -1);
    vector<long long> du(n + 1);
    for (int i = 1; i <= n; i++) du[i] = dist[i];

    // dist from v:
    for (int i = 1; i <= n; i++) dist[i] = -1;
    dist[v] = 0;
    dfs(v, -1);
    vector<long long> dv(n + 1);
    for (int i = 1; i <= n; i++) dv[i] = dist[i];

    long long maxMin = 0;
    for (int i = 1; i <= n; i++)
        maxMin = max(maxMin, min(du[i], dv[i]));

    cout << D + maxMin << "\n";
    return 0;
}
