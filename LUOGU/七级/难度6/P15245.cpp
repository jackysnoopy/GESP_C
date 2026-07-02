#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long x, y;
    cin >> x >> y;
    
    // Operations: x*=2, y*=2, x+=1, y+=1
    // Find minimum operations to make x == y
    
    // Work backwards from y to x
    // Reverse operations: x/=2 (if even), y/=2 (if even), x-=1, y-=1
    
    // Greedy from high bits
    long long ans = 0;
    
    while (x != y) {
        if (x > y) {
            // Need to increase y or decrease x
            // Try dividing x by 2 if possible
            if (x % 2 == 0) {
                x /= 2;
                ans++;
            } else {
                x--;
                ans++;
            }
        } else {
            // y > x
            if (y % 2 == 0) {
                y /= 2;
                ans++;
            } else {
                y--;
                ans++;
            }
        }
    }
    
    cout << ans << "\n";
    return 0;
}
