#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n, count;
vector<string> grid;
vector<vector<bool>> visited;

bool isPalindromic(const string& s) {
    int l = 0, r = s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++;
        r--;
    }
    return true;
}

void dfs(int x, int y, string path) {
    path += grid[x][y];
    
    if (x == n - 1 && y == n - 1) {
        if (isPalindromic(path)) count++;
        return;
    }
    
    if (x + 1 < n && !visited[x + 1][y]) {
        visited[x + 1][y] = true;
        dfs(x + 1, y, path);
        visited[x + 1][y] = false;
    }
    if (y + 1 < n && !visited[x][y + 1]) {
        visited[x][y + 1] = true;
        dfs(x, y + 1, path);
        visited[x][y + 1] = false;
    }
}

int main() {
    int caseNum = 0;
    while (cin >> n && n) {
        grid.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> grid[i];
        }
        
        visited.assign(n, vector<bool>(n, false));
        visited[0][0] = true;
        count = 0;
        dfs(0, 0, "");
        
        cout << "Case " << ++caseNum << ": " << count << endl;
    }
    return 0;
}
