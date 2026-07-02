// UVA133 - The Rolling Ball (滚动球)
// 模拟球在两个10x10网格上的移动
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int n;
    while (cin >> n && n) {
        vector<string> grid(20);
        for (int i = 0; i < 20; i++) {
            grid[i].assign(10, '.');
        }
        // 读取初始球位置
        for (int i = 0; i < n; i++) {
            int side, r, c;
            cin >> side >> r >> c;
            grid[side * 10 + r][c] = 'o';
        }
        string moves;
        cin >> moves;
        // 模拟移动
        // 需要根据题目具体规则实现
        // 此处为框架代码
        for (char m : moves) {
            // 根据移动方向更新球的位置
            // 实现细节依赖于题目完整描述
        }
        // 输出结果
        for (int side = 0; side < 2; side++) {
            for (int r = 0; r < 10; r++) {
                for (int c = 0; c < 10; c++) {
                    cout << grid[side * 10 + r][c];
                }
                cout << "\n";
            }
        }
    }
    return 0;
}
