#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, a, b, s;
    cin >> n >> a >> b >> s;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += arr[i];
    }
    
    cout << ans << endl;
    return 0;
}