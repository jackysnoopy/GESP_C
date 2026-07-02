#include <iostream>
#include <string>
#include <set>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    char dirChar[] = {'E', 'S', 'W', 'N'};
    
    int dir = 0;
    int x = 0, y = 0;
    set<pair<int, int>> scent;
    string instructions;
    
    while (cin >> x >> y >> instructions) {
        cin.ignore();
        
        dir = 0;
        string dirStr;
        cin >> dirStr;
        for (int i = 0; i < 4; i++)
            if (dirStr[0] == dirChar[i]) dir = i;
        
        getline(cin, instructions);
        
        bool lost = false;
        for (char c : instructions) {
            if (lost) break;
            if (c == 'R') dir = (dir + 1) % 4;
            else if (c == 'L') dir = (dir + 3) % 4;
            else if (c == 'F') {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                if (nx < 0 || nx > m || ny < 0 || ny > n) {
                    if (scent.find({x, y}) == scent.end()) {
                        scent.insert({x, y});
                        lost = true;
                    }
                } else {
                    x = nx;
                    y = ny;
                }
            }
        }
        
        cout << x << " " << y << " " << dirChar[dir];
        if (lost) cout << " LOST";
        cout << "\n";
    }
    return 0;
}
