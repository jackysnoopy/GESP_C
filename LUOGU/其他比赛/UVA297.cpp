#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int grid[32][32];

void build(const string& s, int& idx, int r, int c, int size) {
    if (idx >= s.size()) return;
    char ch = s[idx++];
    if (ch == 'p') {
        int half = size / 2;
        build(s, idx, r, c, half);
        build(s, idx, r, c + half, half);
        build(s, idx, r + half, c, half);
        build(s, idx, r + half, c + half, half);
    } else if (ch == 'f') {
        for (int i = r; i < r + size; i++)
            for (int j = c; j < c + size; j++)
                grid[i][j] = 1;
    }
}

int countBlack() {
    int count = 0;
    for (int i = 0; i < 32; i++)
        for (int j = 0; j < 32; j++)
            if (grid[i][j]) count++;
    return count;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        memset(grid, 0, sizeof(grid));
        string s1, s2;
        cin >> s1 >> s2;
        int idx = 0;
        build(s1, idx, 0, 0, 32);
        idx = 0;
        build(s2, idx, 0, 0, 32);
        cout << "There are " << countBlack() << " black pixels." << endl;
    }
    return 0;
}
