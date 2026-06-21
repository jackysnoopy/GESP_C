#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N, W, L;
        cin >> N >> W >> L;

        vector<int> r(N);
        for (int i = 0; i < N; i++) cin >> r[i];

        vector<pair<double, double>> positions;
        double x = 0, y = 0;

        for (int i = 0; i < N; i++) {
            positions.push_back({x, y});
            x += 2 * r[i] + 1;
            if (x > W) {
                x = 0;
                y += 2 * r[i] + 1;
            }
        }

        cout << "Case #" << t << ":";
        for (auto& [x, y] : positions) {
            cout << " " << x << " " << y;
        }
        cout << "\n";
    }

    return 0;
}
