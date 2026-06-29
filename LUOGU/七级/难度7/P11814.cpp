#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    vector<vector<int>> A(k, vector<int>(n));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    
    // 串串问题：构造B序列，最小化max(dist(A_i, B))
    // 对于每个位置j，选择B[j]使得max(|A_i[j] - B[j]|)最小
    
    vector<int> B(n);
    for (int j = 0; j < n; j++) {
        // 找到所有A_i[j]的中位数
        vector<int> vals(k);
        for (int i = 0; i < k; i++) {
            vals[i] = A[i][j];
        }
        sort(vals.begin(), vals.end());
        
        // 选择中位数
        B[j] = vals[k / 2];
    }
    
    for (int j = 0; j < n; j++) {
        if (j > 0) cout << " ";
        cout << B[j];
    }
    cout << "\n";
    
    return 0;
}
