#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 300005;
int n;
long long s;
long long x[MAXN];
int p[MAXN];
vector<int> children[MAXN];
int indegree[MAXN];

int main() {
    scanf("%d %lld", &n, &s);
    
    for (int i = 1; i <= n; i++) {
        scanf("%lld %d", &x[i], &p[i]);
        if (p[i] != 0) {
            children[p[i]].push_back(i);
            indegree[i]++;
        }
    }
    
    // 拓扑排序 + 贪心
    priority_queue<pair<long long, int>> pq;
    vector<bool> done(n + 1, false);
    
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            pq.push({x[i], i});
        }
    }
    
    long long ans = 0;
    long long money = s;
    
    while (!pq.empty()) {
        auto [profit, u] = pq.top();
        pq.pop();
        
        if (done[u]) continue;
        done[u] = true;
        
        if (money + profit >= 0) {
            money += profit;
            ans += profit;
        }
        
        for (int v : children[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                pq.push({x[v], v});
            }
        }
    }
    
    printf("%lld\n", ans);
    return 0;
}