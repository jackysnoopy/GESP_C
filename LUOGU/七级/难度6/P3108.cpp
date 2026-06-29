#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

int n;
long long Bx, By;
map<int, set<int>> rowPos, colPos;
map<pair<int,int>, char> mirType;

pair<int,int> reflect(char t, int dx, int dy) {
    if (t == '\\') return {-dy, -dx};
    return {dy, dx};
}

bool noMirrorBetween(long long x1, long long y1, long long x2, long long y2) {
    if (x1 == x2) {
        long long lo = min(y1, y2), hi = max(y1, y2);
        auto it = colPos.find((int)x1);
        if (it != colPos.end()) {
            auto jt = it->second.upper_bound((int)lo);
            if (jt != it->second.end() && *jt < hi) return false;
        }
        return true;
    } else {
        long long lo = min(x1, x2), hi = max(x1, x2);
        auto it = rowPos.find((int)y1);
        if (it != rowPos.end()) {
            auto jt = it->second.upper_bound((int)lo);
            if (jt != it->second.end() && *jt < hi) return false;
        }
        return true;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> Bx >> By;
    for (int i = 0; i < n; i++) {
        int x, y; char t;
        cin >> x >> y >> t;
        rowPos[y].insert(x);
        colPos[x].insert(y);
        mirType[{x, y}] = t;
    }
    set<pair<long long,long long>> valid;
    long long x = 0, y = 0;
    int dx = 0, dy = 1;
    for (int iter = 0; iter <= n; iter++) {
        long long nx = x, ny = y;
        bool found = false;
        if (dy == 1) {
            auto it = colPos.find((int)x);
            if (it != colPos.end()) {
                auto jt = it->second.upper_bound((int)y);
                if (jt != it->second.end()) { ny = *jt; found = true; }
            }
        } else if (dy == -1) {
            auto it = colPos.find((int)x);
            if (it != colPos.end()) {
                auto jt = it->second.lower_bound((int)y);
                if (jt != it->second.begin()) { --jt; ny = *jt; found = true; }
            }
        } else if (dx == 1) {
            auto it = rowPos.find((int)y);
            if (it != rowPos.end()) {
                auto jt = it->second.upper_bound((int)x);
                if (jt != it->second.end()) { nx = *jt; found = true; }
            }
        } else {
            auto it = rowPos.find((int)y);
            if (it != rowPos.end()) {
                auto jt = it->second.lower_bound((int)x);
                if (jt != it->second.begin()) { --jt; nx = *jt; found = true; }
            }
        }
        if (!found) break;
        for (char mt : {'/', '\\'}) {
            auto [ndx, ndy] = reflect(mt, dx, dy);
            if (ndx == 1 && By == y && Bx > x && Bx < nx && noMirrorBetween(x, y, Bx, By))
                valid.insert({Bx, y});
            else if (ndx == -1 && By == y && Bx < x && Bx > nx && noMirrorBetween(x, y, Bx, By))
                valid.insert({Bx, y});
            else if (ndy == 1 && Bx == x && By > y && By < ny && noMirrorBetween(x, y, Bx, By))
                valid.insert({x, By});
            else if (ndy == -1 && Bx == x && By < y && By > ny && noMirrorBetween(x, y, Bx, By))
                valid.insert({x, By});
        }
        x = nx; y = ny;
        pair<int,int> pos = {(int)x, (int)y};
        if (!mirType.count(pos)) break;
        auto [ndx, ndy] = reflect(mirType[pos], dx, dy);
        dx = ndx; dy = ndy;
    }
    cout << valid.size() << "\n";
    return 0;
}
