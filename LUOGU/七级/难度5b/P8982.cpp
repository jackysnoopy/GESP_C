#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
const long long MAXY = 1000000000000000000LL;
map<long long, long long> mp;
vector<pair<long long, long long>> fall;
void dfs(long long prod, long long y, int last_digit) {
    if (prod > 1 && (mp.find(prod) == mp.end() || y < mp[prod])) {
        mp[prod] = y;
    }
    if (y > MAXY / 10) return;
    for (int d = last_digit; d <= 9; d++) {
        long long new_prod = prod * (d + 1);
        if (new_prod > 50000000LL) break;
        long long new_y = y * 10 + d;
        if (new_y > MAXY) break;
        dfs(new_prod, new_y, d);
    }
}
int main() {
    mp.clear();
    for (int d = 1; d <= 9; d++) {
        dfs(d + 1, d, d);
    }
    for (auto& p : mp) {
        fall.push_back({p.first, p.second});
    }
    sort(fall.begin(), fall.end());
    int Q;
    scanf("%d", &Q);
    while (Q--) {
        long long k;
        scanf("%lld", &k);
        if (k > (long long)fall.size()) {
            printf("-1");
        } else {
            printf("%lld", fall[k - 1].second);
        }
        if (Q > 0) printf(" ");
    }
    printf("\n");
    return 0;
}