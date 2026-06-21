#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    cin >> N >> K;
    vector<int> years(N);
    for (int i = 0; i < N; i++) cin >> years[i];
    sort(years.begin(), years.end());
    vector<int> gaps;
    for (int i = 0; i < N; i++) {
        gaps.push_back(years[i] - (i == 0 ? 0 : years[i-1]) - 12);
    }
    sort(gaps.rbegin(), gaps.rend());
    long long ans = years.back() + 12;
    for (int i = 0; i < min(K - 1, (int)gaps.size()); i++) {
        if (gaps[i] > 0) ans -= gaps[i];
    }
    cout << ans << "\n";
    return 0;
}
