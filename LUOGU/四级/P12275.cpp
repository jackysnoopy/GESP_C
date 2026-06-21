#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    struct Method {
        int x, y, k, w;
    };
    vector<Method> methods(m);
    for (int i = 0; i < m; i++) {
        cin >> methods[i].x >> methods[i].y >> methods[i].k >> methods[i].w;
    }
    
    // Binary search on the answer r
    // For a fixed r, check if max(a[i]/cost[i]) >= r
    // Equivalently, check if max(a[i] - r*cost[i]) >= 0
    // cost[i] = minimum workers per unit of item i
    
    // Actually, the answer is max_i(a[i] / cost[i])
    // where cost[i] = minimum workers per unit
    
    // cost[i] = infinity initially
    // Type 1 (k=0): produces w of item y -> cost[y] = min(cost[y], 1.0/w)
    // Type 2 (k>0): uses k of item x, produces w of item y -> cost[y] = min(cost[y], (cost[x]*k + 1.0)/w)
    
    const double INF = 1e18;
    vector<double> cost(n + 1, INF);
    
    // Process items in order (since x <= y, this is topological order for non-self-loops)
    // First, collect methods by their output item
    vector<vector<Method>> byOutput(n + 1);
    for (auto& mth : methods) {
        byOutput[mth.y].push_back(mth);
    }
    
    // Process in multiple passes since self-loops might need iteration
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 1; i <= n; i++) {
            for (auto& mth : byOutput[i]) {
                if (mth.k == 0) {
                    // Type 1: produces w of item i
                    double newCost = 1.0 / mth.w;
                    if (newCost < cost[i] - 1e-15) {
                        cost[i] = newCost;
                        changed = true;
                    }
                } else {
                    // Type 2: uses k of item x, produces w of item i
                    if (cost[mth.x] < INF / 2) {
                        double newCost = (cost[mth.x] * mth.k + 1.0) / mth.w;
                        if (newCost < cost[i] - 1e-15) {
                            cost[i] = newCost;
                            changed = true;
                        }
                    }
                }
            }
        }
    }
    
    double ans = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] > 0 && cost[i] < INF / 2 && cost[i] > 1e-15) {
            ans = max(ans, (double)a[i] / cost[i]);
        }
    }
    
    printf("%.2f\n", ans);
    return 0;
}
