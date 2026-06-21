#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> min_rep(const vector<int>& a) {
    vector<int> b(2 * 6);
    for (int i = 0; i < 6; i++) b[i] = b[i+6] = a[i];
    
    vector<int> best(6);
    // 顺时针
    for (int s = 0; s < 6; s++) {
        vector<int> cur(6);
        for (int i = 0; i < 6; i++) cur[i] = b[s+i];
        if (s == 0 || cur < best) best = cur;
    }
    // 逆时针
    reverse(b.begin(), b.end());
    for (int s = 0; s < 6; s++) {
        vector<int> cur(6);
        for (int i = 0; i < 6; i++) cur[i] = b[s+i];
        if (cur < best) best = cur;
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    vector<vector<int>> snowflakes;
    for (int i = 0; i < n; i++) {
        vector<int> a(6);
        for (int j = 0; j < 6; j++) cin >> a[j];
        snowflakes.push_back(min_rep(a));
    }
    
    sort(snowflakes.begin(), snowflakes.end());
    for (int i = 1; i < n; i++) {
        if (snowflakes[i] == snowflakes[i-1]) {
            cout << "Twin snowflakes found.\n";
            return 0;
        }
    }
    cout << "No two snowflakes are alike.\n";
    return 0;
}