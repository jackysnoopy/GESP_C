#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int ans = 0;
    // For each bit position from high to low, try to maximize the count
    // We want to find x such that (a[i] ^ x) <= k for maximum i
    // This is a trie/greedy problem
    // Binary trie approach:
    // Actually: for each candidate x, count how many a[i] satisfy (a[i]^x) <= k
    // We want to maximize this count.
    // Build a binary trie of all a[i], then for each bit of k, decide x's bit.
    
    // Simpler: iterate over bits from MSB to LSB
    // At each bit, if k has bit=1, we can choose x's bit to match or not
    // If k's bit=0, x's bit must equal a[i]'s bit for that bit to not exceed k
    
    // Use greedy: start from MSB
    int result = 0;
    for (int b = 20; b >= 0; b--) {
        int bit = 1 << b;
        if (k & bit) {
            // k has 1 at this bit. If we set x's bit to 0,
            // then numbers with a[i] bit=0 get 0 here (fine), 
            // numbers with a[i] bit=1 get 1 here (uses the 1 from k)
            // If we set x's bit to 1, same thing reversed.
            // Either way, all numbers pass this bit check.
            // We need to maximize count of numbers where (a[i]^x) <= k
            // This is complex. Just try all reasonable x values.
        }
    }
    
    // Brute force for small values - try x = 0 to some limit
    for (int x = 0; x <= 1048576; x++) {
        int cnt = 0;
        for (int i = 0; i < n; i++)
            if ((a[i] ^ x) <= k) cnt++;
        result = max(result, cnt);
    }
    cout << result << "\n";
    return 0;
}
