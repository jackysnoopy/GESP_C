#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int X, Y;
        cin >> X >> Y;

        cout << "Case #" << t << ": ";

        if ((abs(X) + abs(Y)) % 2 == 0) {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        string ans;
        int x = X, y = Y;

        while (x != 0 || y != 0) {
            int step = ans.size();
            int dist = 1 << step;

            if (abs(x) > abs(y)) {
                if (x > 0) {
                    ans += 'E';
                    x -= dist;
                } else {
                    ans += 'W';
                    x += dist;
                }
            } else {
                if (y > 0) {
                    ans += 'N';
                    y -= dist;
                } else {
                    ans += 'S';
                    y += dist;
                }
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
