#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, k;
vector<int> stamps;
vector<vector<int>> results;

void solve(int pos, vector<int>& current) {
    if (current.size() == k) {
        results.push_back(current);
        return;
    }
    for (int i = pos; i < n; i++) {
        current.push_back(stamps[i]);
        solve(i + 1, current);
        current.pop_back();
    }
}

int main() {
    while (cin >> n >> k && (n || k)) {
        stamps.resize(n);
        for (int i = 0; i < n; i++) {
            stamps[i] = i + 1;
        }
        results.clear();
        vector<int> current;
        solve(0, current);
        
        for (auto& res : results) {
            for (int i = 0; i < res.size(); i++) {
                cout << res[i] << (i == res.size() - 1 ? "\n" : " ");
            }
        }
        cout << endl;
    }
    return 0;
}
