#include <iostream>
#include <set>
#include <tuple>
using namespace std;

int dx[] = {1, 0, 0, -1};
int dy[] = {0, 1, -1, 0};
char dir[] = "ENWS";

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n && n != 0) {
        int x = 0, y = 0, z = 0;
        set<tuple<int, int, int>> visited;
        visited.insert({0, 0, 0});

        for (int i = 0; i < n; i++) {
            char c;
            int dist;
            cin >> c >> dist;

            int d = 0;
            for (int k = 0; k < 4; k++) {
                if (dir[k] == c) { d = k; break; }
            }

            for (int j = 0; j < dist; j++) {
                x += dx[d];
                y += dy[d];
                auto pos = make_tuple(x, y, z);
                if (visited.find(pos) != visited.end()) {
                    z++;
                    x = 0; y = 0;
                    visited.clear();
                    visited.insert({0, 0, z});
                } else {
                    visited.insert(pos);
                }

            }
        }

        cout << x << " " << y << " " << z << "\n";
    }

    return 0;
}
