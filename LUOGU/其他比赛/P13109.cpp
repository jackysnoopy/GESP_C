#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int P, Q;
        cin >> P >> Q;
        vector<vector<int>> d(Q + 3, vector<int>(Q + 3, 0));
        while (P--) {
            int x, y; char dir;
            cin >> x >> y >> dir;
            if (dir == 'N') {
                int u = x + y, v = x - y + Q;
                if (u <= Q) { d[0][0]++; d[0][v]--; d[u+1][0]--; d[u+1][v]++; }
            } else if (dir == 'S') {
                int u = x + y, v = x - y + Q;
                if (v <= Q) { d[0][v]++; d[u+1][v]--; d[0][Q+1]--; d[u+1][Q+1]++; }
            } else if (dir == 'E') {
                int u = x + y, v = x - y + Q;
                if (v <= Q) { d[0][v]++; d[u+1][v]--; }
                if (u <= Q) { d[0][0]++; d[0][v]--; d[u+1][0]--; d[u+1][v]++; }
            } else if (dir == 'W') {
                int u = x + y, v = x - y + Q;
                if (u <= Q) { d[0][0]++; d[0][v]--; d[u+1][0]--; d[u+1][v]++; }
            }
        }
        int mx = 0, ax = 0, ay = 0;
        for (int i = 0; i <= Q; i++) {
            for (int j = 0; j <= Q; j++) {
                if (i) d[i][j] += d[i-1][j];
                if (j) d[i][j] += d[i][j-1];
                if (i && j) d[i][j] -= d[i-1][j-1];
                if (d[i][j] > mx) { mx = d[i][j]; ax = i; ay = j; }
            }
        }
        cout << ax << " " << ay << "\n";
    }
    return 0;
}
