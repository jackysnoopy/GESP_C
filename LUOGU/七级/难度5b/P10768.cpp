#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // Strategy: connect all nodes to minimize total edge weight
    // Edge weight = a[u] * a[v]
    // To minimize, we want edges with most negative product

    // Key insight: connect all nodes to the node with most negative weight
    // If there are negative weights, connecting positive to negative gives negative products
    // If all non-negative, connect to smallest weight

    // Find the best "hub" node to connect everything to
    // The hub should be the node that minimizes sum of a[hub] * a[i] for all i != hub
    // This is: a[hub] * (sum of all a[i]) - a[hub]^2

    long long total_sum = 0;
    for (int i = 0; i < n; i++) total_sum += a[i];

    // Find hub that minimizes a[hub] * (total_sum - a[hub])
    int hub = 0;
    long long best_val = a[0] * (total_sum - a[0]);
    for (int i = 1; i < n; i++) {
        long long val = a[i] * (total_sum - a[i]);
        if (val < best_val) {
            best_val = val;
            hub = i;
        }
    }

    // Build spanning tree: connect all nodes to hub
    vector<pair<int,int>> edges;
    long long total = 0;

    for (int i = 0; i < n; i++) {
        if (i == hub) continue;
        edges.push_back({hub, i});
        total += a[hub] * a[i];
    }

    // Add extra edges (m - (n-1)) to further minimize
    // Best extra edges: connect nodes with most negative product
    int extra = m - (n - 1);
    if (extra > 0) {
        // Collect all possible edges not yet added
        vector<pair<long long, pair<int,int>>> candidates;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                // Check if edge already exists
                bool exists = false;
                for (auto& e : edges) {
                    if ((e.first == i && e.second == j) || (e.first == j && e.second == i)) {
                        exists = true;
                        break;
                    }
                }
                if (!exists) {
                    candidates.push_back({a[i] * a[j], {i, j}});
                }
            }
        }
        sort(candidates.begin(), candidates.end());

        for (int i = 0; i < extra && i < (int)candidates.size(); i++) {
            edges.push_back(candidates[i].second);
            total += candidates[i].first;
        }
    }

    cout << total << "\n";
    for (auto& e : edges) {
        cout << e.first + 1 << " " << e.second + 1 << "\n";
    }

    return 0;
}
