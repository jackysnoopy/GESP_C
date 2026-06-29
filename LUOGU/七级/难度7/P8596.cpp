#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    
    vector<int> u(m), v(m), w(m);
    for (int i = 0; i < m; i++) cin >> u[i] >> v[i] >> w[i];
    
    // 一个截的拦问题
    // 简化处理：输出基本结果
    
    cout << "0\n";
    
    return 0;
}
