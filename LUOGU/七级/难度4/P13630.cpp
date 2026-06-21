#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<string> files(n);
    for (int i = 0; i < n; i++) cin >> files[i];

    sort(files.begin(), files.end());

    int ans = 0;
    int i = 0;

    while (i < n) {
        ans++;
        string prefix = "";
        int count = 0;

        for (int j = i; j < n && count < k; j++) {
            if (files[j].substr(0, prefix.size()) == prefix) {
                count++;
            } else {
                break;
            }
        }

        if (count >= k) {
            i += count;
        } else {
            i++;
        }
    }

    cout << ans << "\n";
    return 0;
}
