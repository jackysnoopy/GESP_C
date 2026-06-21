#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    string s;
    cin >> n >> s;
    
    vector<int> x(n + 1), y(n + 1);
    x[0] = y[0] = 0;
    for (int i = 0; i < n; i++) {
        x[i+1] = x[i]; y[i+1] = y[i];
        if (s[i] == 'N') y[i+1]++;
        else if (s[i] == 'S') y[i+1]--;
        else if (s[i] == 'E') x[i+1]++;
        else x[i+1]--;
    }
    
    int bestDist = n + 1, bestI = 0, bestJ = 0;
    
    for (int i = 0; i <= n; i++) {
        for (int j = i + 2; j <= n; j++) {
            int dist = abs(x[i] - x[j]) + abs(y[i] - y[j]);
            if (dist < j - i && (dist < bestDist || 
                (dist == bestDist && i < bestI) ||
                (dist == bestDist && i == bestI && j > bestJ))) {
                bestDist = dist;
                bestI = i;
                bestJ = j;
            }
        }
    }
    
    int dx = x[bestJ] - x[bestI];
    int dy = y[bestJ] - y[bestI];
    char dir;
    if (abs(dy) > abs(dx)) dir = (dy > 0) ? 'N' : 'S';
    else if (abs(dx) > abs(dy)) dir = (dx > 0) ? 'E' : 'W';
    else dir = (dy > 0) ? 'N' : (dx > 0) ? 'E' : (dy < 0) ? 'S' : 'W';
    
    cout << bestDist << " " << bestI << " " << bestJ << " " << dir << "\n";
    return 0;
}
