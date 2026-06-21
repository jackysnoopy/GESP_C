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
        int n;
        cin >> n;

        vector<double> x(n), y(n), w(n);
        for (int i = 0; i < n; i++) cin >> x[i] >> y[i] >> w[i];

        double best_x = 0, best_y = 0;
        double best_cost = 1e18;

        for (int iter = 0; iter < 100; iter++) {
            double cx = best_x, cy = best_y;
            double total_w = 0;
            for (int i = 0; i < n; i++) {
                double dx = abs(cx - x[i]);
                double dy = abs(cy - y[i]);
                if (dx > dy) {
                    total_w += w[i];
                } else {
                    total_w += w[i];
                }
            }

            double new_x = 0, new_y = 0, new_w = 0;
            for (int i = 0; i < n; i++) {
                double dx = abs(cx - x[i]);
                double dy = abs(cy - y[i]);
                if (dx >= dy) {
                    new_x += w[i] * x[i];
                    new_y += w[i] * y[i];
                    new_w += w[i];
                }
            }

            if (new_w > 0) {
                best_x = new_x / new_w;
                best_y = new_y / new_w;
            }
        }

        double ans = 0;
        for (int i = 0; i < n; i++) {
            ans += w[i] * max(abs(best_x - x[i]), abs(best_y - y[i]));
        }

        cout << "Case #" << t << ": " << fixed << setprecision(1) << ans << "\n";
    }

    return 0;
}
