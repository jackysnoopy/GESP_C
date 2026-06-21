#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// P1249: 乘积最大
// Split n into parts to maximize product.
// Greedy: use as many 3s as possible, then 2s.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    
    if (n <= 4) {
        if (n == 1) cout << "1\n";
        else if (n == 2) cout << "2\n";
        else if (n == 3) cout << "1 2\n";
        else cout << "2 2\n";
        return 0;
    }
    
    vector<int> parts;
    while (n >= 5) {
        parts.push_back(3);
        n -= 3;
    }
    if (n > 0) parts.push_back(n);
    sort(parts.begin(), parts.end());
    
    for (int i = 0; i < (int)parts.size(); i++) {
        cout << parts[i] << (i + 1 < (int)parts.size() ? " " : "\n");
    }
    return 0;
}
