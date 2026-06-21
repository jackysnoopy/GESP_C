#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        // Split n into parts >= 2. Maximize sum of popcounts.
        // Each part >= 2. popcount(2)=1, popcount(3)=2.
        // For n=2: [2] -> 1.
        // For n=3: [3] -> 2.
        // For n=4: [2,2] -> 1+1=2 or [4] -> 1. Best: 2.
        // For n=5: [2,3] -> 1+2=3.
        // For n=6: [2,2,2] -> 3 or [3,3] -> 4. Best: 4.
        // For n=7: [2,2,3] -> 1+1+2=4 or [3,2,2]=4 or [3,4]=3. Best: 4.
        // For n=8: [3,3,2] -> 2+2+1=5.
        // 
        // Greedy: use as many 3's as possible, then 2's for remainder.
        // 3's give 2 popcount each (best ratio: 2/3).
        // 2's give 1 popcount each (ratio: 1/2).
        // So prefer 3's.
        
        int ans = 0;
        if (n % 3 == 0) {
            ans = (n / 3) * 2;
        } else if (n % 3 == 1) {
            // n = 3k+1. Use (k-1) 3's and two 2's: 3(k-1)+4 = 3k+1 = n.
            // Popcount: 2(k-1)+2 = 2k.
            ans = (n / 3 - 1) * 2 + 2;
        } else {
            // n % 3 == 2. Use k 3's and one 2: 3k+2 = n.
            // Popcount: 2k+1.
            ans = (n / 3) * 2 + 1;
        }
        cout << ans << "\n";
    }
    return 0;
}
