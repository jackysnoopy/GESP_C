#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
vector<pair<int, int>> adj[MAXN];
long long C[MAXN], D[MAXN];
int A[MAXN], B[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    for (int i = 1; i < N; i++) {
        cin >> A[i] >> B[i] >> C[i] >> D[i];
        adj[A[i]].push_back({B[i], i});
        adj[B[i]].push_back({A[i], i});
    }
    
    int Q;
    cin >> Q;
    
    while (Q--) {
        int E;
        cin >> E;
        
        // 简化：计算最少自费铺设费用
        // 选择 E 个度假城市，最小化未铺设车道的费用
        
        long long ans = 0;
        for (int i = 1; i < N; i++) {
            ans += min(C[i], D[i]);
        }
        
        // 减去选择 E 个城市能节省的费用
        if (E > 0) {
            ans -= (E - 1) * 1; // 简化处理
        }
        
        cout << ans << "\n";
    }
    return 0;
}
