#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    unordered_map<int, long long> cnt;
    cnt[0] = 1;
    int mask = 0;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        mask ^= (1 << (s[i] - 'a'));
        ans += cnt[mask];
        cnt[mask]++;
    }
    cout << ans << "\n";
    return 0;
}
