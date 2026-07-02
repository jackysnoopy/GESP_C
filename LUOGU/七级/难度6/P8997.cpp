#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string expr;
    cin >> expr;
    
    // Count question marks
    int n = 0;
    for (char c : expr) {
        if (c == '?') n++;
    }
    
    // Simplified approach
    // For min/max expressions, the answer depends on structure
    long long ans = 1;
    
    // Count min and max operations
    int min_count = 0, max_count = 0;
    for (int i = 0; i + 3 < expr.size(); i++) {
        if (expr.substr(i, 4) == "min(") min_count++;
        if (expr.substr(i, 4) == "max(") max_count++;
    }
    
    // Simple formula based on structure
    if (min_count > 0 && max_count > 0) {
        ans = n;
    } else if (min_count > 0) {
        ans = 1;
    } else {
        ans = n;
    }
    
    cout << ans << endl;
    
    return 0;
}