#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Building {
    double x, y, w, d, h;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int caseno = 0;

    while (cin >> n && n != 0) {
        vector<Building> blds(n);
        vector<double> coords;

        for (int i = 0; i < n; i++) {
            cin >> blds[i].x >> blds[i].y >> blds[i].w >> blds[i].d >> blds[i].h;
            coords.push_back(blds[i].x);
            coords.push_back(blds[i].x + blds[i].w);
        }

        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());

        if (caseno > 0) cout << "\n";
        cout << "For map #" << ++caseno << ", the visible buildings are numbered as follows:\n";

        vector<int> visible;
        for (int i = 0; i < n; i++) {
            bool vis = false;
            for (int j = 0; j + 1 < (int)coords.size(); j++) {
                double mid = (coords[j] + coords[j + 1]) / 2.0;
                if (mid < blds[i].x || mid > blds[i].x + blds[i].w) continue;

                bool blocked = false;
                for (int k = 0; k < n; k++) {
                    if (k == i) continue;
                    if (blds[k].h < blds[i].h) continue;
                    if (blds[k].y >= blds[i].y + blds[i].d) continue;
                    if (blds[k].y + blds[k].d <= blds[i].y) continue;
                    if (blds[k].x <= mid && blds[k].x + blds[k].w >= mid) {
                        blocked = true;
                        break;
                    }
                }
                if (!blocked) {
                    vis = true;
                    break;
                }
            }
            if (vis) visible.push_back(i + 1);
        }

        for (int i = 0; i < (int)visible.size(); i++) {
            if (i > 0) cout << " ";
            cout << visible[i];
        }
        cout << "\n";
    }

    return 0;
}
