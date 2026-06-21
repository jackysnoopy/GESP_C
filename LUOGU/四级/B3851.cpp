#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

int hexToInt(const string &s, int start) {
    int val = 0;
    for (int i = 0; i < 2; i++) {
        char c = s[start + i];
        if (c >= '0' && c <= '9') val = val * 16 + (c - '0');
        else val = val * 16 + (c - 'A' + 10);
    }
    return val;
}

char toHex(int x) {
    if (x < 10) return '0' + x;
    return 'A' + x - 10;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<string> rows(n);
    vector<vector<int>> img(n);
    int cnt[256] = {0};
    
    for (int i = 0; i < n; i++) {
        cin >> rows[i];
        int m = (int)rows[i].length() / 2;
        for (int j = 0; j < m; j++) {
            int val = hexToInt(rows[i], j * 2);
            img[i].push_back(val);
            cnt[val]++;
        }
    }
    
    vector<pair<int,int>> freq;
    for (int i = 0; i < 256; i++) {
        if (cnt[i]) freq.push_back({cnt[i], i});
    }
    sort(freq.begin(), freq.end(), [](const pair<int,int> &a, const pair<int,int> &b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    });
    
    int selected[16];
    int id[256];
    fill(id, id + 256, -1);
    for (int i = 0; i < 16; i++) {
        selected[i] = freq[i].second;
        id[selected[i]] = i;
    }
    
    for (int i = 0; i < 16; i++) {
        cout << toHex(selected[i] / 16) << toHex(selected[i] % 16);
    }
    cout << "\n";
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int)img[i].size(); j++) {
            int val = img[i][j];
            int idx = id[val];
            if (idx == -1) {
                int best = 0, bestDist = 999;
                for (int k = 0; k < 16; k++) {
                    int dist = abs(val - selected[k]);
                    if (dist < bestDist) {
                        bestDist = dist;
                        best = k;
                    }
                }
                idx = best;
            }
            cout << toHex(idx);
        }
        cout << "\n";
    }
    return 0;
}
