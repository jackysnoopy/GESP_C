#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += b[i];
    }
    
    cout << total << "\n";
    
    if (total <= 200000) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < b[i]; j++) {
                cout << i + 1 << " " << i + 1 << "\n";
            }
        }
    }
    
    return 0;
}