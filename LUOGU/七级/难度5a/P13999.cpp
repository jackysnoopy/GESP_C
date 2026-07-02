#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long calculate_diamonds(int N, int M, int K, vector<int> u, vector<int> v, vector<int> d) {
    // 基础实现：简单贪心
    // 对于每个节点，选择最大钻石的边
    vector<int> best_next(N, -1);
    vector<long long> best_diamonds(N, 0);
    
    for (int i = 0; i < M; i++) {
        int from = u[i];
        long long diamonds = d[i];
        if (diamonds > best_diamonds[from]) {
            best_diamonds[from] = diamonds;
            best_next[from] = v[i];
        }
    }
    
    // 简单模拟K步
    long long total = 0;
    int current = 0; // 从节点0开始
    
    for (int step = 0; step < K; step++) {
        if (best_next[current] == -1) {
            break;
        }
        total += best_diamonds[current];
        current = best_next[current];
    }
    
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M, K;
    cin >> N >> M >> K;
    
    vector<int> u(M), v(M), d(M);
    for (int i = 0; i < M; i++) {
        cin >> u[i] >> v[i] >> d[i];
    }
    
    cout << calculate_diamonds(N, M, K, u, v, d) << endl;
    
    return 0;
}