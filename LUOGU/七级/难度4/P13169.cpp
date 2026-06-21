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
        int AC, AJ;
        cin >> AC >> AJ;

        vector<pair<int, int>> cameron, jamie;
        for (int i = 0; i < AC; i++) {
            int c, d;
            cin >> c >> d;
            cameron.push_back({c, d});
        }
        for (int i = 0; i < AJ; i++) {
            int j, k;
            cin >> j >> k;
            jamie.push_back({j, k});
        }

        vector<pair<int, int>> all;
        for (auto& p : cameron) all.push_back(p);
        for (auto& p : jamie) all.push_back(p);
        sort(all.begin(), all.end());

        int exchanges = 2;
        for (int i = 1; i < (int)all.size(); i++) {
            if (all[i].first > all[i - 1].second) exchanges += 2;
        }

        cout << "Case #" << t << ": " << exchanges << "\n";
    }

    return 0;
}
