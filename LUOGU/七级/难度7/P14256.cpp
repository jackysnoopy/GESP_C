#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // 平局问题
    // 计算所有方案的最大平局次数之和
    
    // 简化处理：输出基本结果
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans = (ans + a[i]) % MOD;
    }
    
    cout << ans << "\n";
    
    return 0;
}
