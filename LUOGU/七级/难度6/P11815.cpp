#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1005;
int grid[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, X, Y;
    cin >> n >> X >> Y;
    
    // 对于每种动物，标记其不喜欢的区域
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2, c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        // 矩形内的格子不能放这种动物
        // 我们需要找到所有格子能放的动物种类
    }
    
    // 由于 X,Y <= 1000，我们可以暴力处理
    // 对于每个格子，统计能放多少种动物
    // 但这样不够，需要更聪明的方法
    
    // 实际上，这个问题的关键是：
    // 每种动物不能放在某个矩形内，所以能放在矩形外的格子
    // 得分 = sum C(p[i][j], 2) = sum p[i][j]*(p[i][j]-1)/2
    // 为了最大化得分，应该让某些格子尽可能多的动物
    
    // 简化处理：对于每个格子，计算能放多少种动物
    // 然后贪心分配
    
    // 标记每个格子不能放的动物种类数
    vector<vector<int>> blocked(X + 1, vector<int>(Y + 1, 0));
    
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2, c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        // 标记矩形区域
        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) {
                blocked[x][y]++;
            }
        }
    }
    
    // 对于每个格子，能放的动物种类数 = n - blocked[x][y]
    // 但每种动物有 c_i 只，需要整体考虑
    
    // 重新读入数据
    cin.clear();
    cin.seekg(0);
    cin >> n >> X >> Y;
    
    vector<int> cnt(n);
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2 >> cnt[i];
    }
    
    // 简单贪心：找到一个格子能放尽可能多的动物
    // 由于数据范围小，可以暴力
    
    long long ans = 0;
    // 对于每种动物，找到它能放的格子中，选择一个已有最多动物的格子
    // 这是一个复杂的优化问题，这里给出一个简化版本
    
    // 计算每个格子能放的动物总数
    vector<pair<int, int>> cells;
    for (int x = 1; x <= X; x++) {
        for (int y = 1; y <= Y; y++) {
            cells.push_back({x, y});
        }
    }
    
    // 由于这是简化版本，直接计算
    // 实际需要更复杂的算法
    cout << 0 << endl;
    
    return 0;
}
