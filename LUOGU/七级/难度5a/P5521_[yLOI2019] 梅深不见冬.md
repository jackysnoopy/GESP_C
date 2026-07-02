#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> p(n);
    for (int i = 1; i < n; i++) {
        cin >> p[i];
    }
    
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = w[i];
    }
    
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    
    return 0;
}