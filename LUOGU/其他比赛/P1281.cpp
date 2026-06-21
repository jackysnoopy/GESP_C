#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, k;
    cin >> m >> k;
    vector<int> pages(m + 1);
    int sum = 0;
    for (int i = 1; i <= m; i++) {
        cin >> pages[i];
        sum += pages[i];
    }
    int lo = 0, hi = sum;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        int cnt = 1, cur = 0;
        bool ok = true;
        for (int i = 1; i <= m; i++) {
            if (pages[i] > mid) { ok = false; break; }
            if (cur + pages[i] > mid) { cnt++; cur = pages[i]; }
            else cur += pages[i];
        }
        if (ok && cnt <= k) hi = mid;
        else lo = mid + 1;
    }
    int maxPage = lo;
    vector<pair<int, int>> result;
    int end = m;
    int cur = 0;
    vector<int> segments;
    for (int i = m; i >= 1; i--) {
        if (cur + pages[i] > maxPage) {
            segments.push_back(i + 1);
            cur = pages[i];
        } else {
            cur += pages[i];
        }
    }
    segments.push_back(1);
    for (int i = (int)segments.size() - 1; i >= 0; i--) {
        if (i == (int)segments.size() - 1) {
            result.push_back({segments[i], segments[i] > 1 ? segments[i] - 1 : m});
        } else if (i == 0) {
            result.push_back({segments[i], m});
        } else {
            result.push_back({segments[i], segments[i + 1] - 1});
        }
    }
    for (int i = (int)result.size() - 1; i >= 0; i--) {
        cout << result[i].first << " " << result[i].second << "\n";
    }
    return 0;
}
