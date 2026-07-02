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
    for (int i = 0; i < n; i++) cin >> a[i];
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int cur = 1;
        for (int j = i + 1; j < n; j++) {
            if (a[j] > a[j-1]) cur++;
            else break;
        }
        ans = max(ans, cur);
    }
    
    cout << ans << endl;
    return 0;
}
