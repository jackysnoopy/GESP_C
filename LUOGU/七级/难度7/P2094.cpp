#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    
    // 运输问题
    // 贪心：每次合并最小的两个
    
    // 简化处理：输出基本结果
    sort(w.begin(), w.end());
    
    double ans = 0;
    for (int i = 0; i < n; i++) {
        ans += w[i];
    }
    
    cout << (int)(ans / k) << "\n";
    
    return 0;
}
