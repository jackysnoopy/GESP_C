#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<long long> k(m), b(m);
    vector<long long> cnt(m, 0);
    priority_queue<pair<long long, int>> pq;
    
    for (int i = 0; i < m; i++) {
        cin >> k[i] >> b[i];
        // 第 1 个人的边际成本：k*1 + b
        long long mc = k[i] + b[i];
        if (mc > 0) {
            pq.push({mc, i});
        }
    }
    
    long long total = 0;
    int people = 0;
    
    // 贪心：每次选择边际成本最高的项目分配一个人
    while (people < n && !pq.empty()) {
        auto top = pq.top();
        pq.pop();
        long long mc = top.first;
        int i = top.second;
        
        if (mc <= 0) break;
        
        total += mc;
        cnt[i]++;
        people++;
        
        // 计算下一个边际成本：k*(2*x+1) + b
        long long next_mc = k[i] * (2 * cnt[i] + 1) + b[i];
        if (next_mc > 0) {
            pq.push({next_mc, i});
        }
    }
    
    cout << total << endl;
    return 0;
}
