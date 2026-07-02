#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 100005;
const long long INF = 1e18;

struct Flight {
    int a, b;
};

int main() {
    int N, T;
    scanf("%d %d", &N, &T);
    
    vector<vector<Flight>> flights(N);
    for (int i = 0; i < N - 1; i++) {
        int M;
        scanf("%d", &M);
        flights[i].resize(M);
        for (int j = 0; j < M; j++) {
            scanf("%d %d", &flights[i][j].a, &flights[i][j].b);
        }
    }
    
    int Q;
    scanf("%d", &Q);
    
    for (int i = 0; i < Q; i++) {
        int L, R;
        scanf("%d %d", &L, &R);
        L--; R--;
        
        // BFS计算最短时间
        vector<long long> dist(N, INF);
        dist[L] = 0;
        
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        pq.push({0, L});
        
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            
            if (d > dist[u]) continue;
            if (u == R) break;
            
            for (auto& f : flights[u]) {
                int v = u + 1;
                long long new_dist = d;
                
                // 等待航班
                if (new_dist % T <= f.a) {
                    new_dist += f.a - (new_dist % T);
                } else {
                    new_dist += T - (new_dist % T) + f.a;
                }
                
                // 飞行时间
                new_dist += f.b - f.a;
                
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;
                    pq.push({new_dist, v});
                }
            }
        }
        
        printf("%lld\n", dist[R]);
    }
    
    return 0;
}