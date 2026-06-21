#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N;
        cin >> N;

        vector<pair<string, pair<int, int>>> offers;
        for (int i = 0; i < N; i++) {
            string color;
            int a, b;
            cin >> color >> a >> b;
            offers.push_back({color, {a, b}});
        }

        map<string, vector<pair<int, int>>> color_offers;
        for (auto& offer : offers) {
            color_offers[offer.first].push_back(offer.second);
        }

        int ans = N + 1;

        for (auto& [c1, o1] : color_offers) {
            for (auto& [c2, o2] : color_offers) {
                if (c1 == c2) continue;

                vector<pair<int, int>> combined;
                for (auto& p : o1) combined.push_back(p);
                for (auto& p : o2) combined.push_back(p);

                sort(combined.begin(), combined.end());

                int count = 0;
                int last = 0;
                for (auto& p : combined) {
                    if (p.first > last + 1) {
                        count = N + 1;
                        break;
                    }
                    count++;
                    last = max(last, p.second);
                }

                if (last >= 10000) {
                    ans = min(ans, count);
                }
            }
        }

        if (ans == N + 1) {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
        } else {
            cout << "Case #" << t << ": " << ans << "\n";
        }
    }

    return 0;
}
