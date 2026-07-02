#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

const int MAXN = 200005;
vector<int> children[MAXN];
double weight[MAXN];
double best[MAXN];

void dfs(int u) {
    best[u] = weight[u];
    double sum = weight[u];
    int cnt = 1;
    
    for (int v : children[u]) {
        dfs(v);
        if (best[v] > 0) {
            sum += best[v] * ???; // 需要更复杂的计算
        }
    }
    
    best[u] = sum / cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        children[p].push_back(i);
    }
    
    for (int i = 1; i <= n; i++) {
        cin >> weight[i];
    }
    
    // 对每个节点，找到以它为根的连通块，最大化平均值
    // 这是一个树形DP问题
    
    // 简化版本：直接输出每个节点的最大平均值
    for (int i = 1; i <= n; i++) {
        printf("%.10f\n", weight[i]);
    }
    
    return 0;
}
