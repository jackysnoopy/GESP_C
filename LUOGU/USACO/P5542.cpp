#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    cin >> N >> K;
    vector<array<int,4>> rect(N);
    vector<int> xs, ys;
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        rect[i] = {x1, y1, x2, y2};
        xs.push_back(x1); xs.push_back(x2);
        ys.push_back(y1); ys.push_back(y2);
    }
    sort(xs.begin(), xs.end()); xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end()); ys.erase(unique(ys.begin(), ys.end()), ys.end());
    int nx = xs.size(), ny = ys.size();
    vector<vector<int>> d(nx + 2, vector<int>(ny + 2, 0));
    for (auto &r : rect) {
        int x1 = lower_bound(xs.begin(), xs.end(), r[0]) - xs.begin() + 1;
        int y1 = lower_bound(ys.begin(), ys.end(), r[1]) - ys.begin() + 1;
        int x2 = lower_bound(xs.begin(), xs.end(), r[2]) - xs.begin() + 1;
        int y2 = lower_bound(ys.begin(), ys.end(), r[3]) - ys.begin() + 1;
        d[x1][y1]++; d[x1][y2+1]--; d[x2+1][y1]--; d[x2+1][y2+1]++;
    }
    long long ans = 0;
    for (int i = 1; i <= nx; i++) {
        for (int j = 1; j <= ny; j++) {
            d[i][j] += d[i-1][j] + d[i][j-1] - d[i-1][j-1];
            if (d[i][j] == K)
                ans += (long long)(xs[i-1] - xs[i-2]) * (ys[j-1] - ys[j-2]);
        }
    }
    cout << ans << "\n";
    return 0;
}
