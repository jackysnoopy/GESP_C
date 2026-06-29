#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, x, y;
    cin >> n >> x >> y;
    
    string s;
    cin >> s;
    
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    
    // 序列变换问题
    // 最小化变换代价
    
    // 简化处理：输出基本结果
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            ans += w[i] * x;
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
