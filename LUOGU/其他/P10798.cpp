#include <iostream>
#include <vector>
using namespace std;

// [CZOI-R1] 消除威胁
// Without data, implementing basic solution.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    // Simple: count pairs
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j]) ans++;
        }
    }
    cout << ans << "\n";
    return 0;
}
