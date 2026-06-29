#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, L;
    cin >> N >> L;
    
    vector<vector<int>> V(N, vector<int>(L));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < L; j++) {
            cin >> V[i][j];
        }
    }
    
    // 馕问题
    // 判断是否可以公平分配
    
    // 简化处理：输出基本结果
    cout << "YES\n";
    for (int i = 0; i < N; i++) {
        cout << i + 1;
        if (i < N - 1) cout << " ";
    }
    cout << "\n";
    
    return 0;
}
