#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    long long low = -(1LL << (k - 1));
    long long high = (1LL << (k - 1)) - 1;
    int ans = 0;
    for (int first = 0; first < n; ++first) {
        long long sum = a[first];
        int used = 1;
        vector<int> rem;
        for (int i = 0; i < n; ++i) if (i != first) rem.push_back(a[i]);
        sort(rem.begin(), rem.end());
        while (true) {
            if (sum >= 0) {
                int pos = (int)rem.size();
                while (pos--) if (rem[pos] <= high - sum) break;
                if (pos < 0) break;
                sum += rem[pos];
                rem.erase(rem.begin() + pos);
            } else {
                int pos = 0;
                while (pos < (int)rem.size() && rem[pos] < low - sum) ++pos;
                if (pos == (int)rem.size()) break;
                sum += rem[pos];
                rem.erase(rem.begin() + pos);
            }
            ++used;
        }
        ans = max(ans, used);
    }
    cout << ans << '\n';
    return 0;
}
