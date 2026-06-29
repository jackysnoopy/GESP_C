#include <iostream>
#include <queue>
#include <map>
using namespace std;

int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int xp, yp, xs, ys;
    cin >> xp >> yp >> xs >> ys;
    
    // 对称性：将坐标变换到第一象限
    int x1 = abs(xp - xs);
    int y1 = abs(yp - ys);
    
    // 确保x1 <= y1
    if (x1 > y1) swap(x1, y1);
    
    // 特殊情况
    if (x1 == 0 && y1 == 0) {
        cout << 0 << "\n";
        return 0;
    }
    
    if (x1 == 1 && y1 == 0) {
        cout << 3 << "\n";
        return 0;
    }
    
    if (x1 == 2 && y1 == 2) {
        cout << 4 << "\n";
        return 0;
    }
    
    // 一般情况
    int d = max((y1 + 1) / 2, (x1 + y1 + 2) / 3);
    // 调整奇偶性
    if ((d % 2) != ((x1 + y1) % 2)) d++;
    
    cout << d << "\n";
    return 0;
}