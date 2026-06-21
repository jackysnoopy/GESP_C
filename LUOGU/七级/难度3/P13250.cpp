#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
vector<pair<char,int>> rle(const string& s) {
    vector<pair<char,int>> r;
    for (char c : s) {
        if (r.empty() || r.back().first != c) r.push_back({c, 1});
        else r.back().second++;
    }
    return r;
}
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int N;
        cin >> N;
        vector<string> s(N);
        for (int i = 0; i < N; i++) cin >> s[i];
        vector<vector<pair<char,int>>> enc(N);
        for (int i = 0; i < N; i++) enc[i] = rle(s[i]);
        bool ok = true;
        int len = enc[0].size();
        for (int i = 1; i < N; i++)
            if ((int)enc[i].size() != len) ok = false;
        if (ok) {
            for (int j = 0; j < len; j++)
                for (int i = 1; i < N; i++)
                    if (enc[i][j].first != enc[0][j].first) ok = false;
        }
        cout << "Case #" << tc << ": ";
        if (!ok) { cout << "Fegla Won\n"; continue; }
        int ans = 0;
        for (int j = 0; j < len; j++) {
            vector<int> cnts;
            for (int i = 0; i < N; i++) cnts.push_back(enc[i][j].second);
            sort(cnts.begin(), cnts.end());
            int med = cnts[N / 2];
            for (int v : cnts) ans += abs(v - med);
        }
        cout << ans << "\n";
    }
    return 0;
}
