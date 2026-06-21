#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<string> canvas;

void draw(int n, int x, int y) {
    if (n == 1) {
        canvas[x][y] = 'X';
        return;
    }
    int sz = pow(3, n - 2);
    draw(n - 1, x, y);
    draw(n - 1, x, y + 2 * sz);
    draw(n - 1, x + sz, y + sz);
    draw(n - 1, x + 2 * sz, y);
    draw(n - 1, x + 2 * sz, y + 2 * sz);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (true) {
        int n;
        cin >> n;
        if (n == -1) break;
        
        int sz = 1;
        for (int i = 1; i < n; i++) sz *= 3;
        
        canvas.assign(sz, string(sz, ' '));
        draw(n, 0, 0);
        
        for (const auto& row : canvas)
            cout << row << "\n";
        cout << "-\n";
    }
    return 0;
}