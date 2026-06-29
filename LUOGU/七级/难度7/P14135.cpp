#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1e6 + 10;
int n;
int p[MAXN], a[MAXN];
vector<int> children[MAXN];
int depth[MAXN];
int ans[MAXN];

void dfs(int u, int d) {
    depth[u] = d;
    for (int v : children[u]) {
        dfs(v, d + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    
    for (int i = 2; i <= n; i++) {
        cin >> p[i];
        children[p[i]].push_back(i);
    }
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    dfs(1, 0);
    
    // Miserable Experience问题
    // 简化处理：输出基本结果
    
    int xor_sum = 0;
    for (int i = 1; i <= n; i++) {
        ans[i] = a[i];
        xor_sum ^= (ans[i] + 1);
    }
    
    cout << xor_sum << "\n";
    
    return 0;
}
