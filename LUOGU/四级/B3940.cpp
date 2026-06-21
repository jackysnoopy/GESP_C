#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<vector<int>> a(N, vector<int>(N, 0));
    int r = 0, c = N / 2;
    a[r][c] = 1;
    for (int num = 2; num <= N * N; num++) {
        int nr = (r - 1 + N) % N;
        int nc = (c + 1) % N;
        if (a[nr][nc] != 0) {
            nr = (r + 1) % N;
            nc = c;
        }
        a[nr][nc] = num;
        r = nr;
        c = nc;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j) cout << " ";
            cout << a[i][j];
        }
        cout << "\n";
    }
    return 0;
}
