#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, Q;
    cin >> N >> Q;
    
    vector<vector<pair<int,long long>>> adj(N + 1);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    
    // Precompute distances from node 1 and node N
    vector<long long> dist1(N + 1, -1), distN(N + 1, -1);
    
    auto bfs = [&](int start, vector<long long>& dist) {
        dist[start] = 0;
        vector<int> queue = {start};
        int head = 0;
        while (head < (int)queue.size()) {
            int u = queue[head++];
            for (auto& [v, w] : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + w;
                    queue.push_back(v);
                }
            }
        }
    };
    
    bfs(1, dist1);
    bfs(N, distN);
    
    long long totalDist = dist1[N];
    
    // Track robots: (position, range)
    struct Robot { int pos; long long range; bool active; };
    vector<Robot> robots;
    vector<int> robotScene(Q + 1, -1); // scene when added
    
    for (int j = 1; j <= Q; j++) {
        int type;
        cin >> type;
        
        if (type == 1) {
            int A;
            long long B;
            cin >> A >> B;
            robots.push_back({A, B, true});
            robotScene[j] = robots.size() - 1;
        } else {
            int C;
            cin >> C;
            robots[robotScene[C]].active = false;
        }
        
        // Check if robots can cover the path from 1 to N
        // A robot at position p with range X covers all nodes within distance X
        // The path 1->N has length totalDist
        // We need: for every point on the path, some robot can reach it
        // AND robots can chain together
        
        // Simplified: check if robots can "chain" from 1 to N
        // Robot r covers interval [dist1[pos]-range, dist1[pos]+range] on the path
        // (intersected with [0, totalDist])
        
        vector<pair<long long,long long>> intervals;
        for (auto& r : robots) {
            if (!r.active) continue;
            long long start = dist1[r.pos] - r.range;
            long long end = dist1[r.pos] + r.range;
            start = max(start, 0LL);
            end = min(end, totalDist);
            if (start <= end) {
                intervals.push_back({start, end});
            }
        }
        
        // Check if intervals cover [0, totalDist]
        sort(intervals.begin(), intervals.end());
        
        bool canCover = false;
        long long reach = 0;
        int idx = 0;
        
        while (reach < totalDist && idx < (int)intervals.size()) {
            if (intervals[idx].first > reach) break;
            long long maxReach = reach;
            while (idx < (int)intervals.size() && intervals[idx].first <= reach) {
                maxReach = max(maxReach, intervals[idx].second);
                idx++;
            }
            reach = maxReach;
        }
        
        canCover = (reach >= totalDist);
        cout << (canCover ? "YES" : "NO") << "\n";
    }
    
    return 0;
}