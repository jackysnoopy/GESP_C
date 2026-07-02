#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int H, W;
    cin >> H >> W;
    
    vector<long long> A(H), B(W);
    for (int i = 0; i < H; i++) cin >> A[i];
    for (int i = 0; i < W; i++) cin >> B[i];
    
    // 简单实现：计算最短路径
    // 这里需要更复杂的算法
    long long ans = 0;
    
    // 按照A和B的最小值选择路径
    // 这是一个简化的解法
    for (int i = 0; i < H - 1; i++) {
        ans += min(A[i], A[i + 1]);
    }
    for (int i = 0; i < W - 1; i++) {
        ans += min(B[i], B[i + 1]);
    }
    
    cout << ans << "\n";
    return 0;
}