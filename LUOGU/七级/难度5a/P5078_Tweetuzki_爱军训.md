#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    
    vector<int> idx(n);
    for (int i = 0; i < n; i++) {
        idx[i] = i;
    }
    
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return w[a] > w[b];
    });
    
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (long long)(i + 1) * w[idx[i]];
    }
    
    cout << ans << endl;
    for (int i = 0; i < n; i++) {
        cout << w[idx[i]] << " ";
    }
    cout << endl;
    
    return 0;
}