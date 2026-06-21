#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int M, N, H;
    cin >> M >> N >> H;
    
    vector<vector<int>> a(M, vector<int>(N));
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            cin >> a[i][j];
    
    int ans = -1;
    for (int i = 0; i + 2 < M; i++) {
        for (int j = 0; j + 2 < N; j++) {
            int sum = 0, mx = INT_MIN, mn = INT_MAX;
            for (int di = 0; di < 3; di++) {
                for (int dj = 0; dj < 3; dj++) {
                    int v = a[i+di][j+dj];
                    sum += v;
                    mx = max(mx, v);
                    mn = min(mn, v);
                }
            }
            if (mx - mn <= H)
                ans = max(ans, sum);
        }
    }
    
    cout << ans << '\n';
    return 0;
}