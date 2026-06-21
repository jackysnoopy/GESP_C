#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, I, H, R;
    cin >> N >> I >> H >> R;
    vector<int> d(N + 2, 0);
    set<pair<int,int>> seen;
    while (R--) {
        int a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);
        if (seen.count({a, b})) continue;
        seen.insert({a, b});
        d[a + 1]--; d[b]++;
    }
    int cur = 0;
    for (int i = 1; i <= N; i++) {
        cur += d[i];
        cout << H + cur << "\n";
    }
    return 0;
}
