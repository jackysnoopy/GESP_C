#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, m;
    cin >> N >> m;
    vector<int> k(m);
    for (int i = 0; i < m; i++) cin >> k[i];
    sort(k.begin(), k.end());
    int ans = 0;
    long long sum = 0;
    for (int i = 0; i < m; i++) {
        if (sum + k[i] <= N) {
            sum += k[i];
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
