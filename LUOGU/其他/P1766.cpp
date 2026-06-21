#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Seg {
    long long x1, y1, x2, y2;
    Seg() {}
    Seg(long long a, long long b, long long c, long long d) : x1(a), y1(b), x2(c), y2(d) {}
    long long getLowerX() const { return (y1 < y2) ? x1 : x2; }
    long long getLowerY() const { return min(y1, y2); }
    // Get y at x (assuming x is strictly between x1 and x2)
    // y = y1 + (y2-y1)*(x-x1)/(x2-x1)
    // Return as fraction num/den
    void getY(long long x, long long& num, long long& den) const {
        den = x2 - x1;
        num = y1 * den + (y2 - y1) * (x - x1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long S;
    cin >> n >> S;
    vector<Seg> segs(n);
    for (int i = 0; i < n; i++) {
        cin >> segs[i].x1 >> segs[i].y1 >> segs[i].x2 >> segs[i].y2;
    }
    
    long long curX = S;
    long long curY = (long long)1e18; // start from very high
    
    for (int iter = 0; iter < n + 5; iter++) {
        // Find the highest segment below curY that the drop hits at curX
        int bestSeg = -1;
        long long bestNum = 0, bestDen = 1;
        
        for (int i = 0; i < n; i++) {
            auto& s = segs[i];
            long long lox = min(s.x1, s.x2);
            long long hix = max(s.x1, s.x2);
            // Check if curX is strictly between x1 and x2
            if (curX <= lox || curX >= hix) continue;
            
            long long num, den;
            s.getY(curX, num, den);
            // y = num/den. Check if y < curY (below current position)
            // and y is the highest among candidates
            // Compare num/den with curY: num < curY * den (since den can be negative)
            if (den > 0) {
                if (num >= curY * den) continue; // above current position
            } else {
                if (num <= curY * den) continue; // above current position
            }
            
            if (bestSeg == -1) {
                bestSeg = i;
                bestNum = num;
                bestDen = den;
            } else {
                // Compare num/den with bestNum/bestDen (want highest y)
                __int128 left = (__int128)num * bestDen;
                __int128 right = (__int128)bestNum * den;
                if (den > 0 && bestDen > 0) {
                    if (left > right) { bestSeg = i; bestNum = num; bestDen = den; }
                } else if (den < 0 && bestDen < 0) {
                    if (left > right) { bestSeg = i; bestNum = num; bestDen = den; }
                } else if (den > 0 && bestDen < 0) {
                    // num/den > 0 > bestNum/bestDen
                    if (num > 0) { bestSeg = i; bestNum = num; bestDen = den; }
                }
                // If den < 0 and bestDen > 0, best is higher
            }
        }
        
        if (bestSeg == -1) break;
        
        auto& s = segs[bestSeg];
        curX = s.getLowerX();
        curY = s.getLowerY();
    }
    
    cout << curX << "\n";
    return 0;
}
