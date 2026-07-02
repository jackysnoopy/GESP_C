#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;

int n;
int d[MAXN];
int curDeg[MAXN];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
        curDeg[i] = 0;
    }

    if (n == 2) {
        cout << "1 2\n";
        return;
    }

    vector<int> highDeg, lowDeg;
    for (int i = 1; i <= n; i++) {
        if (d[i] > 1) highDeg.push_back(i);
        else lowDeg.push_back(i);
    }

    vector<pair<int,int>> edges;

    if (highDeg.empty()) {
        for (int i = 1; i < n; i++)
            edges.push_back({i, i + 1});
    } else {
        for (int i = 0; i + 1 < (int)highDeg.size(); i++) {
            edges.push_back({highDeg[i], highDeg[i + 1]});
            curDeg[highDeg[i]]++;
            curDeg[highDeg[i + 1]]++;
        }

        int leafPtr = 0;
        for (int i = 0; i < (int)highDeg.size() && leafPtr < (int)lowDeg.size(); i++) {
            int u = highDeg[i];
            while (curDeg[u] < d[u] && leafPtr < (int)lowDeg.size()) {
                edges.push_back({u, lowDeg[leafPtr++]});
                curDeg[u]++;
            }
        }

        if (leafPtr < (int)lowDeg.size()) {
            for (int i = 0; i + 1 < (int)lowDeg.size() && leafPtr < (int)lowDeg.size(); i++) {
                if (curDeg[lowDeg[i]] < d[lowDeg[i]] && leafPtr < (int)lowDeg.size()) {
                    edges.push_back({lowDeg[i], lowDeg[leafPtr++]});
                    curDeg[lowDeg[i]]++;
                }
            }
        }

        for (int i = 0; i < (int)highDeg.size(); i++) {
            int u = highDeg[i];
            while (curDeg[u] < d[u] && leafPtr < (int)lowDeg.size()) {
                edges.push_back({u, lowDeg[leafPtr++]});
                curDeg[u]++;
            }
        }
    }

    for (auto& e : edges)
        cout << e.first << " " << e.second << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
