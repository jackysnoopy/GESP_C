#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int type;
    cin >> type;
    
    int n;
    cin >> n;
    
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    
    // 造树问题
    // 最大化边的价值和
    
    // 简化处理：输出基本结果
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > 0 && a[j] > 0) {
                ans += (ll)b[i] * b[j];
                a[i]--;
                a[j]--;
            }
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
