#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
    
    sort(a.begin(), a.end());
    vector<int> pos(n);
    for (int i = 0; i < n; i++) pos[i] = a[i].second;
    
    int ans = 1, dir = 1;
    for (int i = 1; i < n; i++) {
        if (pos[i] < pos[i-1] && dir == 1) {
            dir = -1;
        } else if (pos[i] > pos[i-1] && dir == -1) {
            ans++;
            dir = 1;
        }
    }
    
    cout << ans << "\n";
    return 0;
}