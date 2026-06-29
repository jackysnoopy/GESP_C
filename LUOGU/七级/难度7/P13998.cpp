#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    // 夜に駆ける问题
    // 构造矩阵使得机器人路径和最小
    
    // 构造策略：交替放置0和1
    for (int i = 0; i < n; i++) {
        string row;
        for (int j = 0; j < m; j++) {
            if (i % 2 == 0) {
                row += (j % 2 == 0) ? '0' : '1';
            } else {
                row += (j % 2 == 0) ? '1' : '0';
            }
        }
        cout << row << "\n";
    }
    
    return 0;
}
