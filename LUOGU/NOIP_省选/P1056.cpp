#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M, N, K, L, D;
    cin >> M >> N >> K >> L >> D;
    map<int, int> row_cut, col_cut;
    for (int i = 0; i < D; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2) { int c = min(y1, y2); col_cut[c]++; }
        else { int r = min(x1, x2); row_cut[r]++; }
    }
    vector<pair<int,int>> rv(row_cut.begin(), row_cut.end());
    vector<pair<int,int>> cv(col_cut.begin(), col_cut.end());
    sort(rv.begin(), rv.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });
    sort(cv.begin(), cv.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });
    vector<int> rows, cols;
    for (int i = 0; i < K && i < (int)rv.size(); i++) rows.push_back(rv[i].first);
    for (int i = 0; i < L && i < (int)cv.size(); i++) cols.push_back(cv[i].first);
    sort(rows.begin(), rows.end());
    sort(cols.begin(), cols.end());
    for (int i = 0; i < (int)rows.size(); i++) { if (i) cout << " "; cout << rows[i]; }
    cout << "\n";
    for (int i = 0; i < (int)cols.size(); i++) { if (i) cout << " "; cout << cols[i]; }
    cout << "\n";
    return 0;
}
