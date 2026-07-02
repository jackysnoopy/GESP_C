#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> guests(k), bowls(k);
    for (int i = 0; i < k; i++) cin >> guests[i];
    for (int i = 0; i < k; i++) cin >> bowls[i];

    sort(guests.begin(), guests.end());
    sort(bowls.begin(), bowls.end());

    long long ans = LLONG_MAX;

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            int d = ((guests[i] - bowls[j]) % n + n) % n;

            vector<int> shifted(k);
            for (int l = 0; l < k; l++) {
                shifted[l] = (bowls[l] + d) % n;
            }
            sort(shifted.begin(), shifted.end());

            long long cost = 0;
            for (int l = 0; l < k; l++) {
                int diff = abs(guests[l] - shifted[l]);
                cost += min(diff, n - diff);
            }

            ans = min(ans, cost);
        }
    }

    cout << ans << endl;
    return 0;
}
