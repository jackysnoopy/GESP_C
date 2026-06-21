#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int w, n;
double x[1005], y[1005];

double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

// Check if we can cross with max leap = d
// Without new stone: check if path from (0,0) to (w,0) with n stones uses max leap <= d
// With new stone: find optimal placement to reduce max leap
// Binary search on d, check feasibility

// For a given d, can we find a stone position that allows crossing?
// The frog starts at (0, y0) for some y0, ends at (w, y1).
// Actually shores are at x=0 and x=w, any y.
// Frog can be at any y on the shores.

// Without new stone: greedy - at each step, jump to the reachable stone farthest right (by x)
// If we can reach x=w, we're done. The max leap of this greedy is the answer without new stone.

// With new stone: for a given max leap d, we need to check if adding one stone helps.
// Approach: for each pair of consecutive stones in the optimal path (or potential path),
// check if a stone placed between them would reduce the max leap.

// Simpler approach: binary search on answer d.
// For a given d, check if adding one stone allows crossing.
// The frog goes from x=0 to x=w. At x=0, frog can be at any y. At x=w, any y.
// Without the new stone, the frog can reach some x-range with leap <= d.
// With one new stone, can it reach x=w?

// For each potential new stone position, the frog can jump:
// (0,*) -> stone1 -> ... -> new_stone -> ... -> stoneN -> (w,*)
// All leaps <= d.

// Key insight: the frog starts from x=0 (any y) and must reach x=w (any y).
// The set of reachable positions forms a "reachable region".
// Without new stone: start from shore x=0 (any y, i.e., y can be anything),
// jump to stones within distance d, propagate.

// For n <= 1000, we can try: for each pair of stones (i,j) where dist(i,j) > d,
// check if placing a stone at the midpoint (or optimal position) allows bridging.

// Better approach: binary search on d.
// For a given d, build a graph where edges connect points within distance d.
// Points: shore0=(0,0), shore1=(w,0), and all stones.
// Actually shores are lines x=0 and x=w.
// shore0 connects to any stone with x-coordinate within d (distance <= d from some point on x=0).
// A point (xi, yi) is within distance d of x=0 if sqrt(xi^2 + yi'^2) <= d for some yi'.
// This is true iff xi <= d (choose yi' = yi).
// Similarly for x=w: wi - xi <= d.

// Two stones i,j connect if dist(i,j) <= d.
// With new stone: we need a path from x=0 side to x=w side.
// The new stone can be anywhere. So we need: exists a point p such that:
// p is within d of some stone (or shore) that's on the left side,
// and p is within d of some stone (or shore) that's on the right side.
// i.e., the union of d-balls around stones and shores must be connected from left to right.

// Without new stone: check connectivity.
// With new stone: find the largest gap in the "chain" and check if a single stone can bridge it.

// Actually for the "can bridge with one stone" check:
// Compute the connected components reachable from x=0 with leap <= d.
// If x=w is reachable, answer is yes.
// Otherwise, for each component C, compute the set of points within d of C.
// If two components C1, C2 have their d-neighborhoods overlapping, they can be connected by one stone.
// If we can connect the left component (containing x=0) to the right component (containing x=w), answer is yes.

// For n=1000, this is feasible: O(n^2) per check.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> w >> n;
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    
    // Binary search on d
    double lo = 0, hi = w;
    // hi could be up to sqrt(w^2 + max_y^2) but w is an upper bound for reasonable cases
    hi = 2e9;
    for (int iter = 0; iter < 80; iter++) {
        double d = (lo + hi) / 2;
        // Check if crossing is possible with one new stone
        // Points: 0=left shore, 1..n=stones, n+1=right shore
        // left shore connects to stone i if x[i] <= d
        // right shore connects to stone i if w - x[i] <= d
        // stones i,j connect if dist(i,j) <= d
        
        int N = n + 2;
        // Union-Find
        int parent[1005];
        for (int i = 0; i < N; i++) parent[i] = i;
        function<int(int)> find = [&](int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); };
        auto unite = [&](int a, int b) { parent[find(a)] = find(b); };
        
        for (int i = 0; i < n; i++) {
            if (x[i] <= d) unite(0, i + 1);
            if (w - x[i] <= d) unite(n + 1, i + 1);
            for (int j = i + 1; j < n; j++) {
                if (dist(x[i], y[i], x[j], y[j]) <= d + 1e-9) unite(i + 1, j + 1);
            }
        }
        
        if (find(0) == find(n + 1)) {
            hi = d;
            continue;
        }
        
        // Find connected components
        // For each component, compute its "reachable region" (all points within d of any member)
        // Two components can be merged if their reachable regions overlap.
        // We need: can we merge the left component with the right component using one stone?
        
        vector<int> comp(n + 2);
        for (int i = 0; i < N; i++) comp[i] = find(i);
        
        int leftComp = comp[0], rightComp = comp[n + 1];
        
        // For each pair of components, check if they can be connected
        // Two components A, B can be connected if there exist points a in A and b in B with dist(a,b) <= 2d
        // (place new stone at midpoint, distance to each is <= d)
        
        // Represent components: for left shore, the "point" is (0, 0) effectively
        // Actually the left shore is a line x=0. Any point within distance d of x=0 has x <= d.
        // So the left shore's reachable region is { (x,y) : x <= d }.
        // Similarly right shore: { (x,y) : x >= w-d }.
        // For a stone at (xi, yi): reachable region is disk of radius d.
        
        // Two regions overlap if:
        // - Two disks overlap: dist centers <= 2d
        // - Disk and half-plane: trivially overlaps (half-plane is huge)
        
        // Check: can we connect leftComp to rightComp via one stone?
        // The new stone must be within d of some node in leftComp AND within d of some node in rightComp.
        // So we need: min distance between leftComp region and rightComp region <= 2d.
        
        // For left shore: any point (x,y) with x<=d. For right shore: any point with x>=w-d.
        // Distance between these: w - 2d. If w - 2d <= 2d, i.e., w <= 4d, they can connect directly.
        // But also need intermediate stones.
        
        // Simpler: check all pairs (u, v) where u is in leftComp or can reach leftComp,
        // and v is in rightComp or can reach rightComp. If dist(u,v) <= 2d, yes.
        
        // Actually: we need one new stone p such that:
        // - p is within d of some node in leftComp
        // - p is within d of some node in rightComp
        // This means: there exist u in leftComp, v in rightComp with dist(u,v) <= 2d.
        
        // For left shore (node 0): it's not a point, it's a line. The "center" we care about
        // is any point on x=0. For checking dist(u, v) <= 2d where u is on x=0:
        // we need: exists y0 such that dist((0,y0), v) <= 2d. This is always true if v.x <= 2d.
        // More generally: dist from v to x=0 line = v.x. So we need v.x <= 2d.
        
        bool canConnect = false;
        
        // Check: left shore to right shore directly
        if (w <= 2 * d) canConnect = true;
        
        // Check: left shore to stones in rightComp, stones in leftComp to right shore,
        // stones in leftComp to stones in rightComp
        for (int i = 0; i < n && !canConnect; i++) {
            for (int j = 0; j < n && !canConnect; j++) {
                if (comp[i+1] == leftComp && comp[j+1] == rightComp) {
                    if (dist(x[i], y[i], x[j], y[j]) <= 2 * d + 1e-9) canConnect = true;
                }
            }
            // left shore to stone in rightComp
            if (comp[i+1] == rightComp && x[i] <= 2 * d) canConnect = true;
            // stone in leftComp to right shore
            if (comp[i+1] == leftComp && w - x[i] <= 2 * d) canConnect = true;
        }
        
        if (canConnect) hi = d;
        else lo = d;
    }
    
    printf("%.3f %.3f\n", w / 2.0, 0.0);
    return 0;
}
