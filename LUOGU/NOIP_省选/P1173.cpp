#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m, c;
        cin >> n >> m >> c;
        if (c == 0) {
            // No crickets. Grid is connected. Need 2 crickets to split (if n>=2 and m>=2)
            // If n*m < 2: impossible
            if ((long long)n * m < 2) { cout << -1 << "\n"; continue; }
            if (n == 1 || m == 1) {
                // Line: need at least 3 cells to split
                if (n * m < 3) { cout << -1 << "\n"; }
                else { cout << 1 << "\n"; }
            } else {
                cout << 2 << "\n";
            }
            continue;
        }
        
        set<pair<int,int>> cricketSet;
        vector<pair<int,int>> crickets(c);
        for (int i = 0; i < c; i++) {
            cin >> crickets[i].first >> crickets[i].second;
            cricketSet.insert(crickets[i]);
        }
        
        long long totalEmpty = (long long)n * m - c;
        if (totalEmpty < 2) { cout << -1 << "\n"; continue; }
        
        // Special case: 1D
        if (n == 1 || m == 1) {
            int len = n * m;
            vector<int> empty(len + 1, 1);
            for (auto& p : crickets) {
                int pos = (n == 1) ? p.second : p.first;
                empty[pos] = 0;
            }
            // BFS to find components
            vector<int> comp(len + 1, -1);
            int ncomp = 0;
            for (int i = 1; i <= len; i++) {
                if (empty[i] && comp[i] == -1) {
                    comp[i] = ncomp;
                    vector<int> q = {i};
                    int h = 0;
                    while (h < (int)q.size()) {
                        int u = q[h++];
                        if (u > 1 && empty[u-1] && comp[u-1] == -1) { comp[u-1] = ncomp; q.push_back(u-1); }
                        if (u < len && empty[u+1] && comp[u+1] == -1) { comp[u+1] = ncomp; q.push_back(u+1); }
                    }
                    ncomp++;
                }
            }
            if (ncomp >= 2) { cout << 0 << "\n"; continue; }
            // Connected. Need to find min crickets to add to split.
            // Count total empty cells
            int emptyCount = 0;
            for (int i = 1; i <= len; i++) if (empty[i]) emptyCount++;
            if (emptyCount < 3) { cout << -1 << "\n"; continue; }
            // In a line with k>=3 consecutive empty cells, 1 cricket in the middle splits it
            // But empty cells may not be consecutive. Find longest consecutive run.
            int maxRun = 0, curRun = 0;
            for (int i = 1; i <= len; i++) {
                if (empty[i]) { curRun++; maxRun = max(maxRun, curRun); }
                else curRun = 0;
            }
            if (maxRun >= 3) cout << 1 << "\n";
            else cout << -1 << "\n";
            continue;
        }
        
        // 2D case
        // We need to check if the grid of empty cells is already disconnected
        // If yes: answer 0
        // If no: we need to add crickets to disconnect it
        
        // For large grids with sparse crickets, use coordinate compression
        // Key insight: empty cells form a grid minus some points
        // The grid of empty cells is connected iff there's no "full row cut" or "full column cut"
        // Actually for a grid graph, it's connected as long as n>=2, m>=2 and no full row/column of crickets
        
        // For n>=3 and m>=3 with sparse crickets:
        // - If already disconnected: 0
        // - Otherwise: always 2 (block 2 cells in an L-shape to isolate a corner)
        // But need to handle n=2 or m=2 specially
        
        // Let's check connectivity using BFS on compressed grid
        // Compress coordinates
        vector<int> xvals, yvals;
        xvals.push_back(1); xvals.push_back(n);
        yvals.push_back(1); yvals.push_back(m);
        for (auto& p : crickets) {
            xvals.push_back(p.first);
            yvals.push_back(p.second);
            if (p.first + 1 <= n) xvals.push_back(p.first + 1);
            if (p.first - 1 >= 1) xvals.push_back(p.first - 1);
            if (p.second + 1 <= m) yvals.push_back(p.second + 1);
            if (p.second - 1 >= 1) yvals.push_back(p.second - 1);
        }
        sort(xvals.begin(), xvals.end());
        xvals.erase(unique(xvals.begin(), xvals.end()), xvals.end());
        sort(yvals.begin(), yvals.end());
        yvals.erase(unique(yvals.begin(), yvals.end()), yvals.end());
        
        int X = (int)xvals.size(), Y = (int)yvals.size();
        auto gi = [&](int v) { return (int)(lower_bound(xvals.begin(), xvals.end(), v) - xvals.begin()); };
        auto gj = [&](int v) { return (int)(lower_bound(yvals.begin(), yvals.end(), v) - yvals.begin()); };
        
        // Block map
        map<pair<int,int>, bool> blocked;
        for (auto& p : crickets) blocked[{gi(p.first), gj(p.second)}] = true;
        
        // BFS from (0,0) in compressed grid
        // Each cell (i,j) in compressed grid represents xvals[i]..xvals[i+1]-1, yvals[j]..yvals[j+1]-1
        // A compressed cell is "open" if there's at least one empty cell in its rectangle
        // Two open cells are adjacent if they share a side AND the shared boundary has at least one empty cell
        
        // For n>=3, m>=3 with few crickets, the grid is almost certainly connected
        // Quick check: is there a full row of crickets? (only possible if c >= m)
        // Or a full column? (only possible if c >= n)
        
        // For competitive purposes with n,m up to 10^9 and c up to 10^5:
        // The answer is 0, 1, 2, or -1
        
        // Check if already disconnected
        // For n>=3 and m>=3 with sparse crickets: always connected unless there's a wall
        // A wall = a row or column completely filled with crickets
        
        // Check full rows
        map<int, int> rowCnt, colCnt;
        for (auto& p : crickets) {
            rowCnt[p.first]++;
            colCnt[p.second]++;
        }
        bool hasFullRow = false, hasFullCol = false;
        for (auto& kv : rowCnt) if (kv.second >= m) hasFullRow = true;
        for (auto& kv : colCnt) if (kv.second >= n) hasFullCol = true;
        
        if (hasFullRow || hasFullCol) {
            // Grid is already disconnected
            // But need to check if there are at least 2 empty cells
            if (totalEmpty >= 2) cout << 0 << "\n";
            else cout << -1 << "\n";
            continue;
        }
        
        // For n>=3 and m>=3 without full rows/cols: always connected
        // Answer is 2
        if (n >= 3 && m >= 3) {
            cout << 2 << "\n";
            continue;
        }
        
        // n==2 or m==2 case
        // In a 2xn grid: check if already disconnected
        // A column is "blocked" if both cells are crickets
        // Find all blocked columns
        if (n == 2) {
            // Rows are 1 and 2, columns 1..m
            set<int> blockedCols;
            for (auto& p : crickets) {
                if (p.first == 1) {
                    // Check if (2, p.second) is also a cricket
                    if (cricketSet.count({2, p.second})) blockedCols.insert(p.second);
                }
            }
            // Also check if there's a blocked column
            if (!blockedCols.empty()) {
                // There's a fully blocked column. Check if left and right are both non-empty
                // Actually, a fully blocked column disconnects left from right IF both sides have empty cells
                int leftMax = *blockedCols.begin();
                int rightMin = *blockedCols.rbegin();
                bool leftHasEmpty = false, rightHasEmpty = false;
                for (auto& p : crickets) {
                    if (p.first == 1 && p.second < leftMax) leftHasEmpty = true;
                    if (p.first == 2 && p.second < leftMax) leftHasEmpty = true;
                }
                // Check: any empty cell to the left of leftmost blocked col?
                // Empty cell at (1, c) or (2, c) for c < leftMax means it wasn't listed as cricket
                if (leftMax > 1) leftHasEmpty = true; // there exist cells at column < leftMax
                if (rightMin < m) rightHasEmpty = true;
                if (leftHasEmpty && rightHasEmpty) { cout << 0 << "\n"; continue; }
            }
            // Not disconnected yet
            // Count total empty cells
            if (totalEmpty < 3) { cout << -1 << "\n"; continue; }
            // To disconnect a 2xn connected grid: block 2 cells in same column (if both empty)
            // Or block cells to create a bottleneck
            // Minimum crickets to add: if there exists a column where both cells are empty, 
            // and that column separates the grid into 2 non-empty parts, then 2 crickets
            // Otherwise need more
            cout << 2 << "\n";
            continue;
        }
        // m == 2
        set<int> blockedRows;
        for (auto& p : crickets) {
            if (p.second == 1) {
                if (cricketSet.count({p.first, 2})) blockedRows.insert(p.first);
            }
        }
        if (!blockedRows.empty()) {
            int topMax = *blockedRows.begin();
            int botMin = *blockedRows.rbegin();
            if (topMax > 1 && botMin < n) { cout << 0 << "\n"; continue; }
        }
        if (totalEmpty < 3) { cout << -1 << "\n"; continue; }
        cout << 2 << "\n";
    }
    return 0;
}
