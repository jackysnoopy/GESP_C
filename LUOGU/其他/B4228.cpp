#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    map<long long,int> cnt;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    int ans = 0;
    map<long long,int> carry;
    for (auto& p : cnt) {
        long long sz = p.first;
        int c = p.second;
        int avail = c + carry[sz];
        int leftover = avail % 2;
        ans += leftover;
        int can_up = avail / 2;
        if (can_up > 0) carry[sz * 2] += can_up;
    }
    cout << ans << "\n";
    return 0;
}
