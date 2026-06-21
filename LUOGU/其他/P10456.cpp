#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int a[4][4];

void press(int x, int y) {
    for (int i = 0; i < 4; i++) {
        a[x][i] ^= 1;
        a[i][y] ^= 1;
    }
    a[x][y] ^= 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int init = 0;
    for (int i = 0; i < 4; i++) {
        string s; cin >> s;
        for (int j = 0; j < 4; j++)
            if (s[j] == '+') init |= (1 << (i * 4 + j));
    }
    
    int ans_mask = 0, ans_cnt = INT_MAX;
    for (int mask = 0; mask < (1 << 16); mask++) {
        int cur = init;
        int cnt = 0;
        for (int pos = 0; pos < 16; pos++) {
            if (mask >> pos & 1) {
                cnt++;
                int x = pos / 4, y = pos % 4;
                for (int k = 0; k < 4; k++) {
                    cur ^= (1 << (x * 4 + k));
                    cur ^= (1 << (k * 4 + y));
                }
                cur ^= (1 << pos);
            }
        }
        if (cur == 0 && cnt < ans_cnt) {
            ans_cnt = cnt;
            ans_mask = mask;
        }
    }
    
    cout << ans_cnt << "\n";
    for (int pos = 0; pos < 16; pos++)
        if (ans_mask >> pos & 1)
            cout << pos / 4 + 1 << " " << pos % 4 + 1 << "\n";
    return 0;
}