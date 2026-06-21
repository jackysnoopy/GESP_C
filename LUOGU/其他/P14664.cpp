#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // XOR problem. Without full text, implement common XOR approach.
    // Likely: find subarray with maximum XOR or similar.
    // Trie-based approach for max XOR subarray.
    
    // Simple: find maximum XOR of any pair
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ans = max(ans, a[i] ^ a[j]);
        }
    }
    cout << ans << endl;
    return 0;
}
