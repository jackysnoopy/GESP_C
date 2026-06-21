#include <iostream>
#include <climits>
using namespace std;

int a[5][5], tmp[5][5];
int dx[] = {0, -1, 0, 1, 0};
int dy[] = {0, 0, 1, 0, -1};

void press(int x, int y) {
    for (int d = 0; d < 5; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx >= 0 && nx < 5 && ny >= 0 && ny < 5)
            tmp[nx][ny] ^= 1;
    }
}

int solve() {
    int ans = INT_MAX;
    for (int mask = 0; mask < 32; mask++) {
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                tmp[i][j] = a[i][j];
        int cnt = 0;
        
        // 第一行
        for (int j = 0; j < 5; j++) {
            if (mask >> j & 1) {
                press(0, j);
                cnt++;
            }
        }
        
        // 第2-5行递推
        for (int i = 1; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (tmp[i-1][j] == 0) {
                    press(i, j);
                    cnt++;
                }
            }
        }
        
        // 检查最后一行
        bool ok = true;
        for (int j = 0; j < 5; j++)
            if (tmp[4][j] == 0) ok = false;
        
        if (ok) ans = min(ans, cnt);
    }
    return ans <= 6 ? ans : -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        for (int i = 0; i < 5; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < 5; j++)
                a[i][j] = s[j] - '0';
        }
        cout << solve() << "\n";
    }
    return 0;
}