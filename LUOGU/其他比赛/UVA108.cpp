#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    // 读入矩阵
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    
    // 前缀和：计算每行的前缀和
    vector<vector<int>> prefix(n, vector<int>(n + 1, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            prefix[i][j + 1] = prefix[i][j] + matrix[i][j];
        }
    }
    
    int maxSum = -1000000000;  // 初始化为极小值
    
    // 枚举左右边界
    for (int left = 0; left < n; left++) {
        for (int right = left; right < n; right++) {
            // 计算每行在[left, right]范围内的和
            vector<int> rowSum(n, 0);
            for (int i = 0; i < n; i++) {
                rowSum[i] = prefix[i][right + 1] - prefix[i][left];
            }
            
            // Kadane算法求最大子数组和
            int currentSum = 0;
            int bestSum = -1000000000;
            for (int i = 0; i < n; i++) {
                currentSum = max(rowSum[i], currentSum + rowSum[i]);
                bestSum = max(bestSum, currentSum);
            }
            
            maxSum = max(maxSum, bestSum);
        }
    }
    
    cout << maxSum << endl;
    
    return 0;
}
