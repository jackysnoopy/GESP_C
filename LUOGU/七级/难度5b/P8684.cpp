#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
const int MAXN = 300005;
long long a[MAXN], s[MAXN];
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
        }
        s[0] = 0;
        for (int i = 1; i <= n; i++) {
            s[i] = s[i - 1] + a[i];
        }
        vector<long long> even, odd;
        even.push_back(s[0]);
        for (int i = 2; i < n; i += 2) {
            even.push_back(s[i]);
        }
        odd.push_back(s[n]);
        for (int i = n - 1; i >= 1; i -= 2) {
            odd.push_back(s[i]);
        }
        sort(even.begin() + 1, even.end());
        sort(odd.begin() + 1, odd.end());
        long long ans = 0;
        for (int i = 1; i < (int)even.size(); i++) {
            ans = max(ans, even[i] - even[i - 1]);
        }
        for (int i = 1; i < (int)odd.size(); i++) {
            ans = max(ans, odd[i] - odd[i - 1]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}