#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<map<int, int>> rel(n + 1);
        vector<int> cntKnown(n + 1, 0);
        for (int i = 0; i < m; i++) {
            int x, y;
            char w;
            cin >> x >> w >> y;
            int val = (w == '>') ? 2 : 0;
            rel[y][x] = val;
            cntKnown[y]++;
        }
        int best = 0;
        for (int y = 1; y <= n; y++) {
            int worst = 1;
            if (cntKnown[y] < n) {
                worst = 1;
            }
            for (auto& p : rel[y]) {
                if (p.second == 0) {
                    worst = 0;
                    break;
                }
            }
            if (cntKnown[y] == n) {
                worst = 2;
                for (auto& p : rel[y]) {
                    if (p.second < worst) {
                        worst = p.second;
                    }
                }
            }
            if (worst > best) best = worst;
        }
        if (best == 2) cout << "WYGRANA\n";
        else if (best == 1) cout << "REMIS\n";
        else cout << "PRZEGRANA\n";
    }
    return 0;
}
