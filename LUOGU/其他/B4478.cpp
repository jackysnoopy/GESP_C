#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> courses(n);
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        for (int j = 0; j < c; j++) {
            int s, t;
            cin >> s >> t;
            courses[i].push_back({s, t});
        }
    }
    for (int i = 0; i < n; i++) {
        sort(courses[i].begin(), courses[i].end());
    }
    long long current_end = 0;
    for (int i = 0; i < n; i++) {
        long long best_end = -1;
        for (auto& p : courses[i]) {
            if (p.first > current_end) {
                if (best_end == -1 || p.second < best_end) {
                    best_end = p.second;
                }
            }
        }
        if (best_end == -1) {
            cout << -1 << "\n";
            return 0;
        }
        current_end = best_end;
    }
    cout << current_end << "\n";
    return 0;
}
