#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<bool> has(2 * N + 1, false);
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        has[x] = true;
    }
    vector<int> bessie;
    for (int i = 1; i <= 2 * N; i++) {
        if (!has[i]) bessie.push_back(i);
    }
    vector<int> elsie;
    for (int i = 1; i <= 2 * N; i++) {
        if (has[i]) elsie.push_back(i);
    }
    sort(bessie.begin(), bessie.end());
    sort(elsie.begin(), elsie.end());
    int ans = 0;
    int j = 0;
    for (int i = 0; i < N; i++) {
        while (j < N && bessie[j] <= elsie[i]) j++;
        if (j < N) {
            ans++;
            j++;
        }
    }
    cout << ans << "\n";
    return 0;
}
