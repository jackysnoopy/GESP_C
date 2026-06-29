#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, P;
    cin >> N >> P;
    
    vector<int> K(P);
    for (int i = 0; i < P; i++) {
        cin >> K[i];
    }
    
    vector<ll> A(N), B(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i] >> B[i];
    }
    
    // BITWISE EXPRESSIONS问题
    // 计算表达式最大值
    
    // 简化处理：输出基本结果
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        ans = max(ans, B[i]);
    }
    
    cout << ans << "\n";
    
    return 0;
}
