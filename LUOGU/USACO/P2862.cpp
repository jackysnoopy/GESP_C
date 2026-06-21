#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 10001;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int C, N;
    cin >> C >> N;
    
    vector<vector<int>> a(MAXN, vector<int>(MAXN, 0));
    int max_x = 0, max_y = 0;
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        a[x][y]++;
        max_x = max(max_x, x);
        max_y = max(max_y, y);
    }
    
    vector<vector<int>> pre(MAXN + 1, vector<int>(MAXN + 1, 0));
    for (int i = 1; i <= MAXN; i++)
        for (int j = 1; j <= MAXN; j++)
            pre[i][j] = a[i-1][j-1] + pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
    
    auto sum_area = [&](int x1, int y1, int x2, int y2) {
        return pre[x2+1][y2+1] - pre[x1][y2+1] - pre[x2+1][y1] + pre[x1][y1];
    };
    
    int lo = 1, hi = 10000;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        bool ok = false;
        for (int i = 0; i + mid <= 10000 && !ok; i++) {
            for (int j = 0; j + mid <= 10000 && !ok; j++) {
                if (sum_area(i, j, i + mid - 1, j + mid - 1) >= C)
                    ok = true;
            }
        }
        if (ok) hi = mid;
        else lo = mid + 1;
    }
    
    cout << lo << "\n";
    return 0;
}