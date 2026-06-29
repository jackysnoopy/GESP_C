#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
const int MAXN = 1000005;
int s[MAXN];
int main() {
    int n, l, r;
    scanf("%d%d%d", &n, &l, &r);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &s[i]);
    }
    map<int, int> left_first, left_count, right_last, right_count;
    for (int i = 1; i < l; i++) {
        left_count[s[i]]++;
        if (left_first.find(s[i]) == left_first.end()) {
            left_first[s[i]] = i;
        }
    }
    for (int i = r + 1; i <= n; i++) {
        right_count[s[i]]++;
        right_last[s[i]] = i;
    }
    vector<pair<int, int>> left_unique, right_unique;
    for (auto& p : left_first) {
        if (left_count[p.first] == 1) {
            left_unique.push_back({p.first, p.second});
        }
    }
    for (auto& p : right_last) {
        if (right_count[p.first] == 1) {
            right_unique.push_back({p.first, p.second});
        }
    }
    int ans = n + 1;
    for (auto& lu : left_unique) {
        for (auto& ru : right_unique) {
            if (lu.first != ru.first) {
                ans = min(ans, ru.second - lu.second + 1);
            }
        }
    }
    if (ans > n) {
        printf("-1\n");
    } else {
        printf("%d\n", ans);
    }
    return 0;
}