#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    
    // 记录操作
    vector<pair<int, int>> ops;
    
    // 贪心策略：从上到下、从左到右处理
    // 对于每个亮着的灯泡，尝试通过反转行或列来关闭
    
    // 第一遍：处理前n-1行和前n-1列
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (grid[i][j] == 1) {
                // 反转第i行
                ops.push_back({i + 1, 0});
                for (int c = 0; c < n; c++) {
                    grid[i][c] ^= 1;
                }
            }
        }
    }
    
    // 处理最后一列（前n-1行）
    for (int i = 0; i < n - 1; i++) {
        if (grid[i][n - 1] == 1) {
            // 反转第i行
            ops.push_back({i + 1, 0});
            for (int c = 0; c < n; c++) {
                grid[i][c] ^= 1;
            }
        }
    }
    
    // 处理最后一行（前n-1列）
    for (int j = 0; j < n - 1; j++) {
        if (grid[n - 1][j] == 1) {
            // 反转第j列
            ops.push_back({0, j + 1});
            for (int r = 0; r < n; r++) {
                grid[r][j] ^= 1;
            }
        }
    }
    
    // 处理右下角的灯泡
    if (grid[n - 1][n - 1] == 1) {
        // 如果k>0，可以直接反转这个灯泡
        if (k > 0) {
            ops.push_back({n, n});
            grid[n - 1][n - 1] ^= 1;
            k--;
        } else {
            // 尝试其他方案
            // 反转最后一行和最后一列
            ops.push_back({n, 0});
            ops.push_back({0, n});
            for (int c = 0; c < n; c++) {
                grid[n - 1][c] ^= 1;
            }
            for (int r = 0; r < n; r++) {
                grid[r][n - 1] ^= 1;
            }
            // 右下角被翻转了两次，所以还是1
            // 需要再反转一次
            grid[n - 1][n - 1] ^= 1;
        }
    }
    
    // 检查是否全部关闭
    bool allOff = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                allOff = false;
                break;
            }
        }
        if (!allOff) break;
    }
    
    if (!allOff) {
        cout << -1 << endl;
        return 0;
    }
    
    // 输出操作
    cout << ops.size() << endl;
    for (const auto& op : ops) {
        cout << op.first << " " << op.second << endl;
    }
    
    return 0;
}
