#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    string s;
    if (!(cin >> N >> s)) return 0;
    vector<int> ones;
    for (int i = 0; i < N; ++i) if (s[i] == '1') ones.push_back(i);
    if (ones.empty()) { cout << (N > 1 ? N - 1 : 0) << '\n'; return 0; }
    int base = 0;
    for (int i = 1; i < (int)ones.size(); ++i) base = max(base, ones[i] - ones[i - 1]);
    auto can = [&](int D) -> bool {
        if (D <= base) return true;
        if (D > N) return false;
        int need = 2;
        int prev = ones[0];
        for (int i = 1; i < (int)ones.size(); ++i) {
            if (ones[i] - prev >= D) { prev = ones[i]; continue; }
            if (need == 0) return false;
            --need;
            int p = prev + D;
            if (p > ones[i]) return false;
            if (need > 0) {
                --need;
                if (p + D <= ones[i]) prev = ones[i];
                else prev = p;
            } else {
                prev = ones[i];
            }
        }
        return need == 0;
    };
    int lo = 1, hi = N + 1;
    while (lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if (can(mid)) lo = mid; else hi = mid - 1;
    }
    cout << lo << '\n';
    return 0;
}
