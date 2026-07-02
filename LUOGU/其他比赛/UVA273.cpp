#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Segment {
    int x1, y1, x2, y2;
};

bool onSegment(int px, int py, int x1, int y1, int x2, int y2) {
    return min(x1, x2) <= px && px <= max(x1, x2) &&
           min(y1, y2) <= py && py <= max(y1, y2);
}

int cross(int ox, int oy, int ax, int ay, int bx, int by) {
    return (ax - ox) * (by - oy) - (ay - oy) * (bx - ox);
}

bool intersect(Segment a, Segment b) {
    int d1 = cross(b.x1, b.y1, b.x2, b.y2, a.x1, a.y1);
    int d2 = cross(b.x1, b.y1, b.x2, b.y2, a.x2, a.y2);
    int d3 = cross(a.x1, a.y1, a.x2, a.y2, b.x1, b.y1);
    int d4 = cross(a.x1, a.y1, a.x2, a.y2, b.x2, b.y2);
    
    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
        return true;
    }
    
    if (d1 == 0 && onSegment(a.x1, a.y1, b.x1, b.y1, b.x2, b.y2)) return true;
    if (d2 == 0 && onSegment(a.x2, a.y2, b.x1, b.y1, b.x2, b.y2)) return true;
    if (d3 == 0 && onSegment(b.x1, b.y1, a.x1, a.y1, a.x2, a.y2)) return true;
    if (d4 == 0 && onSegment(b.x2, b.y2, a.x1, a.y1, a.x2, a.y2)) return true;
    
    return false;
}

int parent[201];

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int x, int y) {
    parent[find(x)] = find(y);
}

int main() {
    int T;
    cin >> T;
    bool first = true;
    while (T--) {
        int n;
        cin >> n;
        vector<Segment> segs(n);
        for (int i = 0; i < n; i++) {
            cin >> segs[i].x1 >> segs[i].y1 >> segs[i].x2 >> segs[i].y2;
        }
        
        for (int i = 0; i < n; i++) parent[i] = i;
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (intersect(segs[i], segs[j])) {
                    unite(i, j);
                }
            }
        }
        
        int q;
        cin >> q;
        while (q--) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            if (!first) cout << "\n";
            first = false;
            if (find(a) == find(b)) {
                cout << "CONNECTED\n";
            } else {
                cout << "NOT CONNECTED\n";
            }
        }
    }
    return 0;
}
