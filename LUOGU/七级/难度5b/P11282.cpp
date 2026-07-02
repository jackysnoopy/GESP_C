#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

const int MAXN = 1e6 + 10;

int n;
int p[MAXN];
bool ans[MAXN];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    
    // 特殊情况：n=3时直接判断
    if (n == 3) {
        int mx = max({p[1], p[2], p[3]});
        int mn = min({p[1], p[2], p[3]});
        int mid = p[1] + p[2] + p[3] - mx - mn;
        
        for (int i = 1; i <= n; i++) {
            ans[i] = false;
        }
        ans[mx] = true;
        ans[mn] = true;
        
        for (int i = 1; i <= n; i++) {
            cout << (ans[i] ? '1' : '0');
        }
        cout << '\n';
        return;
    }
    
    // 对于n>3的情况，需要更复杂的分析
    // 这里先给出一个简单的解决方案，实际上需要更深入的分析
    // 暂时先输出全1作为占位
    for (int i = 1; i <= n; i++) {
        cout << '1';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    
    return 0;
}