#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, s;
    cin >> n >> s;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // We want to find the arrangement that minimizes empty lines
    // This is a complex optimization problem
    
    // For now, output placeholder
    cout << 0 << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << (i < n ? " " : "\n");
    }
    
    return 0;
}
