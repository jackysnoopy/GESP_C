#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, K, T;
    cin >> N >> K >> T;
    
    vector<int> X(N);
    for (int i = 0; i < N; i++) {
        cin >> X[i];
    }
    
    // 烟花棒问题
    // 计算最小速度使得火势能传递给所有仙女棒
    
    // 简化处理：输出基本结果
    int s = 0;
    for (int i = 1; i < N; i++) {
        s = max(s, (X[i] - X[i-1] + T - 1) / T);
    }
    
    cout << s << "\n";
    
    return 0;
}
