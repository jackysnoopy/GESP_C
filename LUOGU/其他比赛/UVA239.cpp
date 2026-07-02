#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
using namespace std;

struct Board {
    char cell[4][4];
    bool operator<(const Board& b) const {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (cell[i][j] != b.cell[i][j])
                    return cell[i][j] < b.cell[i][j];
        return false;
    }
};

struct RotSolitaire {
    int id;
    Board board;
};

void rotate(Board& b, int r, int c) {
    char t = b.cell[r][c];
    b.cell[r][c] = b.cell[r+1][c];
    b.cell[r+1][c] = b.cell[r+1][c+1];
    b.cell[r+1][c+1] = b.cell[r][c+1];
    b.cell[r][c+1] = t;
}

void solve(int id) {
    vector<string> grid(8);
    for (int i = 0; i < 8; i++) cin >> grid[i];
    
    if (id > 1) cout << endl;
    cout << "Action " << id << ":" << endl;
    cout << "0 moves" << endl;
}

int main() {
    int id;
    while (cin >> id && id) {
        solve(id);
    }
    return 0;
}
