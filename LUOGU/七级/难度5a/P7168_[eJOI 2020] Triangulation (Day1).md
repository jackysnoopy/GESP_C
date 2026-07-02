#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<pair<int, int>> corners(n);
    for (int i = 0; i < n; i++) {
        cin >> corners[i].first >> corners[i].second;
    }
    
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = i + 1;
    }
    
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
    
    return 0;
}