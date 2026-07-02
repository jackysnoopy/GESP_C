#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n != 0) {
        vector<Point> points(n);
        set<pair<int,int>> pointSet;
        
        for (int i = 0; i < n; i++) {
            cin >> points[i].x >> points[i].y;
            pointSet.insert({points[i].x, points[i].y});
        }
        
        set<vector<pair<int,int>>> squares;
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int x1 = points[i].x, y1 = points[i].y;
                int x2 = points[j].x, y2 = points[j].y;
                
                int dx = x2 - x1;
                int dy = y2 - y1;
                
                // Two possible squares for this edge
                // Square 1: rotate (dx, dy) by +90 degrees
                int nx1_1 = x2 - dy;
                int ny1_1 = y2 + dx;
                int nx2_1 = x1 - dy;
                int ny2_1 = y1 + dx;
                
                // Square 2: rotate (dx, dy) by -90 degrees
                int nx1_2 = x2 + dy;
                int ny1_2 = y2 - dx;
                int nx2_2 = x1 + dy;
                int ny2_2 = y1 - dx;
                
                // Check square 1
                if (nx1_1 >= 0 && nx1_1 <= 20 && ny1_1 >= 0 && ny1_1 <= 20 &&
                    nx2_1 >= 0 && nx2_1 <= 20 && ny2_1 >= 0 && ny2_1 <= 20) {
                    if (pointSet.count({nx1_1, ny1_1}) && pointSet.count({nx2_1, ny2_1})) {
                        vector<pair<int,int>> square = {
                            {x1, y1}, {x2, y2}, {nx1_1, ny1_1}, {nx2_1, ny2_1}
                        };
                        sort(square.begin(), square.end());
                        squares.insert(square);
                    }
                }
                
                // Check square 2
                if (nx1_2 >= 0 && nx1_2 <= 20 && ny1_2 >= 0 && ny1_2 <= 20 &&
                    nx2_2 >= 0 && nx2_2 <= 20 && ny2_2 >= 0 && ny2_2 <= 20) {
                    if (pointSet.count({nx1_2, ny1_2}) && pointSet.count({nx2_2, ny2_2})) {
                        vector<pair<int,int>> square = {
                            {x1, y1}, {x2, y2}, {nx1_2, ny1_2}, {nx2_2, ny2_2}
                        };
                        sort(square.begin(), square.end());
                        squares.insert(square);
                    }
                }
            }
        }
        
        cout << squares.size() << "\n";
    }
    
    return 0;
}