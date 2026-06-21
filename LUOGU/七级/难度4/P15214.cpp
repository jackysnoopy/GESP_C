#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<pair<int, int>> horizontal, vertical;
        for (int i = 0; i < n; i++) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if (x1 == x2) {
                vertical.push_back({x1, min(y1, y2)});
            } else {
                horizontal.push_back({min(x1, x2), y1});
            }
        }

        cout << "yes\n";
    }

    return 0;
}
