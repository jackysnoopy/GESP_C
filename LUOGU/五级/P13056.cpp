#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        long long X, Y;
        cin >> X >> Y;
        
        // 如果 X 和 Y 都是偶数或者都是奇数，是不可能的
        if ((X + Y) % 2 == 0) {
            cout << "Case #" << t << ": IMPOSSIBLE" << endl;
            continue;
        }
        
        // 确定需要的跳跃次数
        int n = 0;
        long long dist = abs(X) + abs(Y);
        while ((1LL << n) - 1 < dist) {
            n++;
        }
        
        string result = "";
        long long curX = 0, curY = 0;
        
        // 从大到小尝试每个跳跃
        for (int i = n - 1; i >= 0; i--) {
            long long step = 1LL << i;
            
            // 计算当前位置到目标的方向
            long long dx = X - curX;
            long long dy = Y - curY;
            
            // 优先移动距离大的方向
            if (abs(dx) >= abs(dy)) {
                if (dx > 0) {
                    curX += step;
                    result += "E";
                } else {
                    curX -= step;
                    result += "W";
                }
            } else {
                if (dy > 0) {
                    curY += step;
                    result += "N";
                } else {
                    curY -= step;
                    result += "S";
                }
            }
        }
        
        reverse(result.begin(), result.end());
        cout << "Case #" << t << ": " << result << endl;
    }
    
    return 0;
}
