#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    long long total_cake = 0;
    vector<int> cakes(n);
    for (int i = 0; i < n; i++) {
        cin >> cakes[i];
        total_cake += cakes[i];
    }
    
    int m;
    cin >> m;
    
    vector<int> mouths(m);
    for (int i = 0; i < m; i++) {
        cin >> mouths[i];
    }
    
    sort(mouths.begin(), mouths.end());
    
    long long used = 0;
    int ans = 0;
    
    for (int i = 0; i < m; i++) {
        if (used + mouths[i] <= total_cake) {
            used += mouths[i];
            ans++;
        } else {
            break;
        }
    }
    
    cout << ans << "\n";
    return 0;
}
