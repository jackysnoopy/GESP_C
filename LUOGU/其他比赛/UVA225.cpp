#include <iostream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    int T;
    cin >> T;
    bool first = true;
    while (T--) {
        if (!first) cout << "\n";
        first = false;
        string s;
        cin >> s;
        int n = s.length();
        // Directions: 0=N, 1=E, 2=S, 3=W
        int dx[] = {0, 1, 0, -1};
        int dy[] = {1, 0, -1, 0};
        int dir = 0;
        int x = 0, y = 0;
        map<pair<int,int>, int> vis;
        vis[{x, y}] = 1;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'L') dir = (dir + 3) % 4;
            else if (s[i] == 'R') dir = (dir + 1) % 4;
            else if (s[i] == 'F') {
                x += dx[dir];
                y += dy[dir];
                vis[{x, y}]++;
            }
        }
        int minx = 1e9, maxx = -1e9, miny = 1e9, maxy = -1e9;
        for (auto& p : vis) {
            minx = min(minx, p.first.first);
            maxx = max(maxx, p.first.first);
            miny = min(miny, p.first.second);
            maxy = max(maxy, p.first.second);
        }
        int w = maxx - minx + 1;
        int h = maxy - miny + 1;
        int offsetx = -minx;
        int offsety = -miny;
        vector<string> grid(h, string(w, ' '));
        for (auto& p : vis) {
            int gx = p.first.first + offsetx;
            int gy = p.first.second + offsety;
            grid[gy][gx] = '0' + min(p.second, 9);
        }
        grid[offsety][offsetx] = '*';
        for (int i = h - 1; i >= 0; i--) {
            cout << grid[i] << "\n";
        }
    }
    return 0;
}
