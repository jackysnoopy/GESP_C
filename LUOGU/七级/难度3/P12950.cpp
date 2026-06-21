#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        string s;
        cin >> s;
        int n = s.size();
        if (n <= 1) { cout << "Case #" << tc << ": 0\n"; continue; }
        vector<pair<char,int>> runs;
        for (int i = 0; i < n; i++) {
            if (runs.empty() || runs.back().first != s[i])
                runs.push_back({s[i], 1});
            else
                runs.back().second++;
        }
        int ans = 0;
        if (runs.size() == 1) {
            ans = (n + 1) / 2;
        } else if (s[0] == s[n-1]) {
            int mergedLen = runs[0].second + runs.back().second;
            ans = (mergedLen + 1) / 2;
            for (int i = 1; i + 1 < (int)runs.size(); i++)
                ans += runs[i].second / 2;
        } else {
            for (auto& r : runs)
                ans += r.second / 2;
        }
        cout << "Case #" << tc << ": " << ans << "\n";
    }
    return 0;
}
