#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Agent {
    int r, c;
    char dir;
    int steps;
};

int R, C;
char grid[21][21];
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int dirChar(char c) {
    if (c == 'N') return 0;
    if (c == 'E') return 1;
    if (c == 'S') return 2;
    if (c == 'W') return 3;
    return -1;
}

int main() {
    int cases = 0;
    while (cin >> R >> C && (R || C)) {
        cases++;
        
        vector<Agent> agents;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                cin >> grid[i][j];
                if (grid[i][j] == 'N' || grid[i][j] == 'S' || 
                    grid[i][j] == 'E' || grid[i][j] == 'W') {
                    Agent a;
                    a.r = i;
                    a.c = j;
                    a.dir = grid[i][j];
                    agents.push_back(a);
                }
            }
        }
        
        for (auto& a : agents) {
            int d = dirChar(a.dir);
            int r = a.r, c = a.c;
            bool blocked = false;
            for (int step = 1; step <= R * C; step++) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) {
                    blocked = true;
                    break;
                }
                if (grid[nr][nc] != '.') {
                    blocked = true;
                    break;
                }
                r = nr;
                c = nc;
            }
            a.r = r;
            a.c = c;
        }
        
        vector<vector<char>> result(R, vector<char>(C, '.'));
        for (auto& a : agents) {
            result[a.r][a.c] = '*';
        }
        
        cout << "Simulation " << cases << endl;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++)
                cout << result[i][j];
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
