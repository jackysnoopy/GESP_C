#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long H;
    cin >> n >> H;
    vector<long long> w(n);
    bool possible = true;
    for (int i = 0; i < n; i++) {
        long long l, wi, h;
        cin >> l >> wi >> h;
        // For each book, find minimum width among orientations where height <= H
        long long minW = -1;
        // Orientation 1: height = l, width = wi (depth = h)
        if (l <= H) { if (minW == -1 || wi < minW) minW = wi; }
        // Orientation 2: height = l, width = h (depth = wi)
        if (l <= H) { if (minW == -1 || h < minW) minW = h; }
        // Orientation 3: height = wi, width = l
        if (wi <= H) { if (minW == -1 || l < minW) minW = l; }
        // Orientation 4: height = wi, width = h
        if (wi <= H) { if (minW == -1 || h < minW) minW = h; }
        // Orientation 5: height = h, width = l
        if (h <= H) { if (minW == -1 || l < minW) minW = l; }
        // Orientation 6: height = h, width = wi
        if (h <= H) { if (minW == -1 || wi < minW) minW = wi; }
        if (minW == -1) { possible = false; break; }
        w[i] = minW;
    }
    if (!possible) {
        cout << "impossible" << endl;
    } else {
        long long total = 0;
        for (int i = 0; i < n; i++) total += w[i];
        cout << total << endl;
    }
    return 0;
}
