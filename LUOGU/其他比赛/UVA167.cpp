#include <iostream>
#include <algorithm>
using namespace std;

int board[8][8];
int ans;
int cols[8], diag1[15], diag2[15];

void dfs(int row, int sum) {
    if (row == 8) {
        ans = max(ans, sum);
        return;
    }
    for (int c = 0; c < 8; c++) {
        if (!cols[c] && !diag1[row + c] && !diag2[row - c + 7]) {
            cols[c] = diag1[row + c] = diag2[row - c + 7] = 1;
            dfs(row + 1, sum + board[row][c]);
            cols[c] = diag1[row + c] = diag2[row - c + 7] = 0;
        }
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                cin >> board[i][j];
        ans = 0;
        fill(cols, cols + 8, 0);
        fill(diag1, diag1 + 15, 0);
        fill(diag2, diag2 + 15, 0);
        dfs(0, 0);
        cout << ans << endl;
    }
    return 0;
}
