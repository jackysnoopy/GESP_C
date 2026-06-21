#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Grid: row i has cells (i,1) to (i,a[i]).
    // Start at (1,1), end at (n, max_column_of_row_n).
    // Can move up, down, right. Can revisit cells (counted once).
    // Maximize unique cells visited.
    //
    // Key idea: we can visit all cells in the "reachable" region.
    // We must go from row 1 to row n, moving right only.
    // At each row, we can go up/down to explore.
    // The constraint: can only move right, so column only increases.
    // We can go up/down freely (revisiting is fine, counted once).
    //
    // Optimal strategy: 
    // Go down column 1 to the row where a[i] is maximum, then go right.
    // But actually, we can zigzag.
    //
    // Think of it as: we visit some set of cells. Each cell (r,c) must have c <= a[r].
    // The path goes from (1,1) to (n, a[n]-1...a[n]-1+1... wait, end is (n, max(a[n]-1+1...)).
    // Actually end is (n, a[n])? No: "第 n 行最右边的格子" = (n, a[n]).
    //
    // We can only move right, up, or down. So column never decreases.
    // At column c, we can visit all rows r where a[r] >= c.
    // We want to maximize total unique cells = sum over columns c of (number of rows with a[r] >= c 
    //   that we actually visit at column c).
    //
    // Actually: the answer is the total number of cells in the "reachable" region.
    // The reachable region is: all cells (r,c) such that c <= a[r] and the cell is 
    // connected to (1,1) via a path that only moves right, up, or down.
    //
    // The connectivity constraint: at column c, we can be at any row r where a[r] >= c,
    // as long as we can reach that row from column c-1.
    // At column c-1, we could be at any row r where a[r] >= c-1.
    // From there, we move right to (r, c), then up/down to any row r' where a[r'] >= c.
    // The rows we can reach at column c are exactly those in the same "connected component"
    // as (1,1) at column c-1, plus any row r where a[r] >= c and a[r] >= c-1 (already connected).
    //
    // Simpler: the reachable cells are all cells (r,c) where:
    // 1. c <= a[r]
    // 2. The cell is in the "monotone connected component" starting from (1,1).
    //
    // Actually, since we can go up/down freely at any column, the only constraint is:
    // - We start at (1,1).
    // - We can reach column c only if there's a path of columns where each consecutive 
    //   pair shares at least one row.
    // - At column c, we can visit all rows r where a[r] >= c, as long as that row is 
    //   "reachable" (connected to some row at column c-1 that is also >= c, or c=1).
    //
    // Since at column 1 we can reach all rows r where a[r] >= 1 (which is all rows),
    // and we can move up/down freely, we can reach ALL cells (r,c) where c <= a[r].
    // Wait, that can't be right for sample 1: a=[1,2], answer=3.
    // Total cells = 1+2 = 3. So yes, all cells are reachable.
    // Sample 2: a=[1,1,4,5,1,4], answer=9.
    // Total cells = 1+1+4+5+1+4 = 16. Answer is 9. So NOT all cells are reachable.
    //
    // The issue: row 5 has a[5]=1, so at column 2+, we can't be in row 5.
    // But we need to pass through row 5 to get to row 6 at column 2+.
    // Actually: from row 4 (a[4]=5), we can go right to column 2, then down to row 5 only 
    // if a[5] >= 2. But a[5]=1, so we can't. But we don't need to go to row 5 at column 2.
    // We can go from row 4 at column 1 directly to row 6 at column 1 (a[6]=4 >= 1).
    // Then at row 6, go right to column 4.
    //
    // So the constraint is: at column c, the rows we can visit form a contiguous interval
    // [min_row, max_row] where all rows in between have a[r] >= c.
    // Actually it's the connected components of rows where a[r] >= c.
    //
    // The answer is: for each column c, count how many rows in the reachable component have a[r] >= c.
    // The reachable component at column c is the component containing row 1 if a[1] >= c,
    // extended by connectivity through rows with a[r] >= c.
    //
    // But we start at row 1. So the reachable component is the connected component of 
    // rows with a[r] >= c that contains row 1 (if a[1] >= c).
    //
    // For sample 2: a=[1,1,4,5,1,4]
    // c=1: all rows have a[r]>=1, connected. Reachable = 6 rows. Cells = 6.
    // c=2: rows with a[r]>=2: rows 3,4,6. But row 5 has a[5]=1 < 2, so rows 3,4 and 6 
    //   are separate components. Row 1 has a[1]=1 < 2, so we can't start at column 2.
    //   Wait, we CAN be at column 2 if we moved right from column 1.
    //   At column 1, we could be at any row. Moving right from row r to column 2 requires a[r] >= 2.
    //   So at column 2, reachable rows = those with a[r]>=2 that are connected through 
    //   rows with a[r]>=2 to some row that was reachable at column 1 AND has a[r]>=2.
    //   Rows with a[r]>=2: 3,4,6. Row 3 and 4 are adjacent (both >=2), row 5 is 1 < 2 (breaks).
    //   So component 1: {3,4}, component 2: {6}.
    //   At column 1, we could reach row 3 (via row 1->2->3, all >=1). So component {3,4} is reachable.
    //   Row 6: from column 1, we can be at row 6 (a[6]=4>=1), and a[6]=4>=2, so we can move right.
    //   So row 6 is also reachable at column 2.
    //   Wait, but to get from column 1 row 6 to column 2 row 6, we just move right. 
    //   And a[6]=4 >= 2. So yes, row 6 is reachable at column 2.
    //   Actually, at column 1, we can reach ANY row (all have a>=1). So at column 2, 
    //   any row with a[r]>=2 is reachable (by moving right from that row at column 1).
    //   So reachable at c=2: rows 3,4,6. Cells = 3.
    // c=3: rows with a[r]>=3: rows 3,4,6. All reachable. Cells = 3.
    // c=4: rows with a[r]>=4: rows 3,4,6. Cells = 3.
    // c=5: rows with a[r]>=5: row 4 only. Cells = 1.
    // Wait, row 6 has a[6]=4 < 5. So c=5: only row 4.
    // But row 4 is reachable (from column 1 row 4, move right to column 5).
    // Hmm wait, a[4]=5 >= 5, yes.
    // Total = 6+3+3+3+1 = 16. But answer is 9!
    //
    // I'm misunderstanding the problem. Let me re-read.
    // "你需要从第 1 行最左边的格子走到第 n 行最右边的格子"
    // Start: (1,1). End: (n, a[n]).
    // "你走的过程中只能向上、下或右方向"
    // "不能走出网格"
    // "但是可以重复走某个格子，重复走的只算一次"
    //
    // The path must be a SINGLE PATH from (1,1) to (n, a[n]).
    // It's not about visiting all reachable cells. It's about the maximum cells on a single path.
    //
    // So we need a path from (1,1) to (n, a[n]) that visits maximum unique cells.
    // Since we can go up/down/right, and revisit cells:
    // The optimal path goes: from (1,1), go right as slowly as possible, exploring rows.
    // 
    // Key insight: at each column, we can visit at most a contiguous set of rows.
    // The path must go from column 1 to column a[n], visiting rows along the way.
    //
    // Let me think of it as: at column c, we're at some row. We can go up/down (staying at col c)
    // to visit all rows r with a[r] >= c that are in the same connected component.
    // Then we move right to column c+1.
    //
    // The optimal strategy: at each column, visit all reachable rows, then move right.
    // But we can also go right, then come back (up/down), then go right again.
    // Actually no: we can't go left. So once we move right, we can't go back.
    //
    // Hmm, but we CAN revisit cells. So at column c, we go up/down to visit all reachable rows,
    // then move right to column c+1. At column c+1, we can again go up/down.
    //
    // But the reachable rows at column c+1 depend on which row we're at when we enter column c+1.
    // If we enter at row r (from column c), we can go up/down at column c+1 to visit all rows
    // in the connected component of rows with a[r'] >= c+1 that contains r.
    //
    // So the answer is: at each column c, count the rows in the reachable connected component.
    // Sum over all columns.
    //
    // But which component do we end up in? We want to maximize total.
    // At column 1: we're at row 1. Component = all rows with a[r]>=1 = all rows.
    // We visit all n rows at column 1.
    // At column 2: we can enter at any row r with a[r]>=2 (since we were at row r at column 1
    //   and moved right). Actually we can only enter at the row we were at when we moved right.
    //   But we can choose which row to move right from!
    //   So at column 1, after visiting all rows, we choose a row r with a[r]>=2 and move right.
    //   At column 2, we can visit all rows in r's component (rows with a[r']>=2 connected to r).
    //
    // So the greedy is: at each column, choose the row to enter from that maximizes the component.
    //
    // This is a complex DP. Let me think of it as:
    // For each column c, the reachable cells = size of the connected component of rows
    // with a[r]>=c that intersects with ALL previous columns' reachable sets.
    //
    // Actually simpler: since at column 1 we can reach all rows, and at each subsequent column
    // we can choose which row to enter from, the reachable set at column c is:
    // ALL rows r with a[r]>=c (since at column 1 we can reach any row, and we can always
    // move to that row at column 1, then move right through columns 2..c-1... but wait,
    // we can only move right, not left. So to reach row r at column c, we need to have been
    // at row r at column c-1 (or reached it via up/down at column c).
    //
    // I think the answer is: sum over c=1 to max_a of (number of rows with a[r]>=c 
    //   that are in the same connected component as row 1 in the subgraph of rows with a[r]>=c).
    // Wait, row 1 might not have a[1]>=c for c>=2.
    //
    // Let me just do a BFS/DFS approach.
    // Answer = total cells in the connected region reachable from (1,1) using only right, up, down.
    
    int maxCol = *max_element(a.begin(), a.end());
    // Build grid connectivity. Two cells are connected if adjacent (up/down/right/left).
    // But we can only move right, up, down (NOT left).
    // So connectivity is: from (r,c), can go to (r-1,c), (r+1,c), (r,c+1).
    // BFS from (1,1).
    
    // But grid can be up to 100x100. BFS is fine.
    vector<vector<bool>> vis(n, vector<bool>(maxCol + 1, false));
    // a[i] is 1-indexed in problem but 0-indexed in code
    // Row i (0-indexed) has cells (i, 1) to (i, a[i]).
    // Start at (0, 0) in 0-indexed = (1,1) in problem.
    // End at (n-1, a[n-1]-1) in 0-indexed.
    
    // Actually let me use 1-indexed for rows and columns.
    // Visited cells
    int ans = 0;
    // BFS/DFS: from (r,c), go to (r-1,c), (r+1,c), (r,c+1) if valid.
    // But this doesn't work because we might revisit cells.
    // Since we count unique cells, just BFS from (1,1) with these 3 directions.
    
    // Use a set or grid to track visited.
    vector<vector<bool>> visited(n + 1, vector<bool>(maxCol + 2, false));
    // BFS
    vector<pair<int,int>> stack;
    stack.push_back(make_pair(1, 1));
    visited[1][1] = true;
    int dx[] = {-1, 1, 0};
    int dy[] = {0, 0, 1};
    int head = 0;
    while (head < (int)stack.size()) {
        int r = stack[head].first;
        int c = stack[head].second;
        head++;
        ans++;
        for (int d = 0; d < 3; d++) {
            int nr = r + dx[d];
            int nc = c + dy[d];
            if (nr >= 1 && nr <= n && nc >= 1 && nc <= a[nr - 1] && !visited[nr][nc]) {
                visited[nr][nc] = true;
                stack.push_back(make_pair(nr, nc));
            }
        }
    }
    cout << ans << endl;
    return 0;
}
