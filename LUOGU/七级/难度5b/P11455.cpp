#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> occ(n + 1);
    for (int i = 0; i < n; i++) {
        occ[a[i]].push_back(i);
    }
    vector<int> gaps;
    int numLabels = 0;
    for (int label = 1; label <= n; label++) {
        if (occ[label].empty()) continue;
        numLabels++;
        for (int j = 1; j < (int)occ[label].size(); j++) {
            gaps.push_back(occ[label][j] - occ[label][j - 1]);
        }
    }
    sort(gaps.begin(), gaps.end());
    for (int x = 1; x <= n; x++) {
        int g = (int)(gaps.end() - upper_bound(gaps.begin(), gaps.end(), x));
        cout << numLabels + g << "\n";
    }
    return 0;
}
