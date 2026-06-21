#include <iostream>
#include <vector>
using namespace std;

struct Line {
    long long s, e, d;
};

long long count(const vector<Line>& lines, long long x) {
    long long sum = 0;
    for (const auto& l : lines) {
        if (l.s > x) continue;
        long long end = min(l.e, x);
        sum += (end - l.s) / l.d + 1;
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<Line> lines(n);
        long long max_e = 0;
        for (int i = 0; i < n; i++) {
            cin >> lines[i].s >> lines[i].e >> lines[i].d;
            max_e = max(max_e, lines[i].e);
        }
        
        if (count(lines, max_e) % 2 == 0) {
            cout << "There's no weakness.\n";
            continue;
        }
        
        long long lo = 1, hi = max_e;
        while (lo < hi) {
            long long mid = (lo + hi) / 2;
            if (count(lines, mid) & 1)
                hi = mid;
            else
                lo = mid + 1;
        }
        
        long long cnt = count(lines, lo) - count(lines, lo - 1);
        cout << lo << " " << cnt << "\n";
    }
    return 0;
}