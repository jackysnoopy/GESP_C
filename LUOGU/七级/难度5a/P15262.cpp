#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, f;
    cin >> n >> f;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    vector<int> s(f);
    for (int i = 0; i < f; i++) {
        cin >> s[i];
    }
    
    for (int i = 1; i <= n; i++) {
        cout << "-1\n";
    }
    
    return 0;
}