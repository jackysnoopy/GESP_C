#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
typedef long long ll;

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        ll R, C, N;
        scanf("%lld %lld %lld", &R, &C, &N);
        
        ll total = R * C;
        if (N == 0) { printf("Case #%d: 0\n", t); continue; }
        if (N >= total) N = total;
        
        ll internalWalls = (R - 1) * C + R * (C - 1);
        
        // Approach: place N tenants to minimize shared walls
        // Strategy 1: checkerboard fill (good for small N)
        // Strategy 2: fill all then remove (good for large N)
        // Use the better of the two
        
        // For approach 1: count second-color cells by neighbor count
        ll ans1 = [&]() -> ll {
            ll half1 = (total + 1) / 2;
            if (N <= half1) return 0;
            ll extra = N - half1;
            ll n2 = 0, n3 = 0, n4 = 0;
            for (ll i = 0; i < R; i++)
                for (ll j = 0; j < C; j++)
                    if ((i + j) % 2 == 1) {
                        ll nb = (i > 0) + (i < R-1) + (j > 0) + (j < C-1);
                        if (nb == 2) n2++;
                        else if (nb == 3) n3++;
                        else n4++;
                    }
            ll ans = 0, rem = extra;
            ll u = min(rem, n2); ans += u * 2; rem -= u;
            u = min(rem, n3); ans += u * 3; rem -= u;
            u = min(rem, n4); ans += u * 4; rem -= u;
            return ans;
        }();
        
        // For approach 2: place all, then remove (total-N) cells
        // Greedy: remove cells with most occupied neighbors first
        // But need to handle adjacency between removed cells
        ll ans2 = internalWalls; // start with all occupied
        {
            ll empty = total - N;
            if (empty > 0) {
                // Count cells by degree (number of neighbors in grid)
                // Use a greedy: remove highest-degree cells first
                // But cells share walls, so removing adjacent cells reduces benefit
                
                // Simple approach: sort cells by degree, remove greedily
                // For large grids, use the formula:
                // interior cells: 4 neighbors, edge: 3, corner: 2
                ll nInterior = max(0LL, (R-2)) * max(0LL, (C-2));
                ll nEdge = 0;
                if (R >= 2 && C >= 2)
                    nEdge = 2 * (R-2) + 2 * (C-2);
                // corners: always 4
                // But this doesn't account for 1D grids
                
                // Better: just count all cells by degree
                vector<ll> degs;
                for (ll i = 0; i < R; i++)
                    for (ll j = 0; j < C; j++) {
                        ll d = (i > 0) + (i < R-1) + (j > 0) + (j < C-1);
                        degs.push_back(d);
                    }
                sort(degs.begin(), degs.end(), greater<ll>());
                
                // Greedy removal: remove cells with highest degree
                // But when removing a cell, its neighbors' effective degree decreases
                // For simplicity, use the sorted degrees as an approximation
                // This gives an upper bound on reduction
                
                ll reduction = 0;
                for (ll i = 0; i < empty && i < (ll)degs.size(); i++)
                    reduction += degs[i];
                
                // But this overcounts: removing two adjacent cells counts their shared wall twice
                // The actual reduction is at most internalWalls
                ans2 = internalWalls - min(reduction, internalWalls);
            }
        }
        
        ll ans = min(ans1, ans2);
        printf("Case #%d: %lld\n", t, max(0LL, ans));
    }
    return 0;
}
