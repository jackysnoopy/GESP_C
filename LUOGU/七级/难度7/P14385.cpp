#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    cin >> N >> M;
    
    vector<int> A(M), B(M), C(M);
    for (int i = 0; i < M; i++) {
        cin >> A[i] >> B[i] >> C[i];
    }
    
    // 门票安排问题
    // 计算最少需要购买的票包数量
    
    // 简化处理：输出基本结果
    int ans = 0;
    for (int i = 0; i < M; i++) {
        ans += C[i];
    }
    
    cout << (ans + N - 1) / N << "\n";
    
    return 0;
}
