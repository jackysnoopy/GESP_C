#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    
    // Calculate net change needed for each pile
    vector<int> diff(n);
    for (int i = 0; i < n; i++) {
        diff[i] = b[i] - a[i];
    }
    
    // Calculate prefix sums of diff
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + diff[i];
    }
    
    // The answer is the sum of absolute values of prefix sums
    // divided by n (for circular distance)
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += abs(prefix[i]);
    }
    
    cout << ans << "\n";
    return 0;
}
