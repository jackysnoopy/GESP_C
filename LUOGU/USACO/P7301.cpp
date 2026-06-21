#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    // 2x2 constraint: every 2x2 block has exactly 2 cows.
    // This means the pattern is one of two types:
    // Type 1: checkerboard with rows alternating
    // Type 2: checkerboard with columns alternating
    // Actually, the valid patterns are:
    // Pattern A: columns alternate (even cols filled, odd cols empty, or vice versa)
    // Pattern B: rows alternate (even rows filled, odd rows empty, or vice versa)
    // 
    // For Pattern A (column-based):
    //   For each column j, decide: fill even rows or odd rows.
    //   Column j: if j is even, fill even rows; if j is odd, fill odd rows (or vice versa).
    //   Wait, that's not quite right.
    //
    // Actually, the constraint "every 2x2 has exactly 2" means:
    // For any 2x2 block at (i,j), (i,j+1), (i+1,j), (i+1,j+1):
    //   a[i][j] + a[i][j+1] + a[i+1][j] + a[i+1][j+1] = 2
    // This means: a[i][j] + a[i+1][j+1] = a[i][j+1] + a[i+1][j]
    // i.e., a[i][j] - a[i][j+1] = a[i+1][j] - a[i+1][j+1]
    // So the difference between adjacent columns is the same for all rows.
    // This means all rows have the same "column pattern".
    // The column pattern is: alternate between two values (0 and 1, or 1 and 0).
    // So there are two column patterns: 0101... and 1010...
    // For each column, we choose one of the two patterns.
    // But the 2x2 constraint means adjacent columns must have opposite patterns.
    // So the column pattern is determined by the first column.
    // Two possibilities: even columns have pattern A, odd columns have pattern B.
    //
    // Wait, let me reconsider. The constraint is:
    // For every 2x2 block, exactly 2 cells are filled.
    // This means: in each 2x2 block, either:
    // - Top-left and bottom-right are filled (diagonal 1)
    // - Top-right and bottom-left are filled (diagonal 2)
    // - Top row filled (but then bottom row must also have 2 filled, which means all 4 are filled - contradiction)
    // - etc.
    //
    // Actually: the constraint is that every 2x2 has exactly 2. The possible patterns for a 2x2:
    // CC.. (top row) -> 2 cows. But the 2x2 below must also have 2. So bottom row is either CC or ..CC or C.C. etc.
    //
    // Let me think about it differently. Define b[i][j] = 1 if cow at (i,j), 0 otherwise.
    // For every 2x2: b[i][j] + b[i][j+1] + b[i+1][j] + b[i+1][j+1] = 2.
    // This implies: b[i][j] + b[i+1][j+1] = b[i][j+1] + b[i+1][j] = 1 (since each pair sums to 1).
    // Wait, that's not necessarily true. b[i][j] + b[i][j+1] + b[i+1][j] + b[i+1][j+1] = 2
    // means b[i][j] + b[i+1][j+1] = 2 - (b[i][j+1] + b[i+1][j]).
    // This doesn't directly give us the pattern.
    //
    // Let me try: b[i][j] = (i + j) % 2 XOR p for some bit p.
    // Then in a 2x2 block: b[i][j] + b[i][j+1] + b[i+1][j] + b[i+1][j+1]
    // = ((i+j)%2^p) + ((i+j+1)%2^p) + ((i+j+1)%2^p) + ((i+j+2)%2^p)
    // = ((i+j)%2^p) + (1-(i+j)%2^p) + (1-(i+j)%2^p) + ((i+j)%2^p)
    // = 2*(i+j)%2^p + 2*(1-(i+j)%2^p) = 2. ✓
    //
    // But wait, this only works for p=0 or p=1. And it gives a checkerboard pattern.
    // But the sample solution uses a non-checkerboard pattern:
    // CC.. / ..CC / CC.. / ..CC
    // Let me check: b[0][0]=1, b[0][1]=1, b[0][2]=0, b[0][3]=0
    //              b[1][0]=0, b[1][1]=0, b[1][2]=1, b[1][3]=1
    //              b[2][0]=1, b[2][1]=1, b[2][2]=0, b[2][3]=0
    //              b[3][0]=0, b[3][1]=0, b[3][2]=1, b[3][3]=1
    // 2x2 at (0,0): 1+1+0+0 = 2. ✓
    // 2x2 at (0,1): 1+0+0+1 = 2. ✓
    // 2x2 at (0,2): 0+0+1+1 = 2. ✓
    // This is NOT a checkerboard! It's rows alternating.
    //
    // So the valid patterns are:
    // 1. Checkerboard (b[i][j] = (i+j)%2)
    // 2. Rows alternate (b[i][j] = i%2)
    // 3. Columns alternate (b[i][j] = j%2)
    //
    // Wait, let me check pattern 2: b[i][j] = i%2.
    // 2x2 at (0,0): 0+0+1+1 = 2. ✓ (if i%2=0 for row 0, i%2=1 for row 1)
    // 2x2 at (0,1): 0+0+1+1 = 2. ✓
    // But also: b[i][j] = 1-i%2 works (fill even rows).
    //
    // And pattern 3: b[i][j] = j%2.
    // 2x2 at (0,0): 0+1+0+1 = 2. ✓
    // 2x2 at (0,1): 1+0+1+0 = 2. ✓
    //
    // But are there other patterns? Let me check: b[i][j] = (i%2) XOR (j%2).
    // That's the checkerboard. ✓
    //
    // What about: b[i][j] = 1 if (j%2 == 0) else 0, for all i?
    // Same as pattern 3 with offset.
    //
    // What about: for each row, independently choose to fill even or odd columns?
    // Row 0: fill even cols. Row 1: fill odd cols. Row 2: fill even cols.
    // 2x2 at (0,0): 1+0+0+1 = 2. ✓
    // 2x2 at (0,1): 0+1+1+0 = 2. ✓
    // This works! But it's the checkerboard.
    //
    // What about: Row 0: fill even cols. Row 1: fill even cols.
    // 2x2 at (0,0): 1+0+1+0 = 2. ✓
    // 2x2 at (0,1): 0+1+0+1 = 2. ✓
    // This is pattern 3 (columns alternate).
    //
    // So the valid patterns are:
    // A. Fill cells where j%2 == 0 (columns alternate)
    // B. Fill cells where j%2 == 1 (columns alternate, shifted)
    // C. Fill cells where i%2 == 0 (rows alternate)
    // D. Fill cells where i%2 == 1 (rows alternate, shifted)
    // E. Fill cells where (i+j)%2 == 0 (checkerboard)
    // F. Fill cells where (i+j)%2 == 1 (checkerboard, shifted)
    //
    // Wait, but can we mix? E.g., columns 0,2,4... fill even rows, columns 1,3,5... fill odd rows?
    // That's the checkerboard pattern.
    //
    // What about: for each column, independently choose to fill even or odd rows?
    // Col 0: even rows. Col 1: even rows.
    // 2x2 at (0,0): 1+1+0+0 = 2. ✓
    // 2x2 at (0,1): 1+1+0+0 = 2. ✓
    // 2x2 at (1,0): 0+0+1+1 = 2. ✓
    // This is pattern C (rows alternate).
    //
    // Col 0: even rows. Col 1: odd rows.
    // 2x2 at (0,0): 1+0+0+1 = 2. ✓
    // 2x2 at (0,1): 0+1+1+0 = 2. ✓
    // This is the checkerboard.
    //
    // So the only valid patterns are the 6 listed above (A-F).
    // Let me verify: are there any other patterns?
    //
    // Consider a 3x3 grid. If we fix the first row and first column, the rest is determined.
    // Row 0: b[0][0], b[0][1], b[0][2]
    // Col 0: b[0][0], b[1][0], b[2][0]
    // 2x2 at (0,0): b[0][0]+b[0][1]+b[1][0]+b[1][1] = 2 => b[1][1] = 2-b[0][0]-b[0][1]-b[1][0]
    // 2x2 at (0,1): b[0][1]+b[0][2]+b[1][1]+b[1][2] = 2 => b[1][2] = 2-b[0][1]-b[0][2]-b[1][1]
    // etc.
    //
    // So the pattern is determined by the first row and first column.
    // But the first row must satisfy: b[0][j] + b[0][j+1] + b[1][j] + b[1][j+1] = 2.
    // And b[1][j] is determined by the first column.
    //
    // This is getting complex. Let me just enumerate the 6 patterns and compute the max beauty for each.
    // Then take the max over all 6.
    
    int ans = 0;
    // Pattern A: fill (i,j) where j%2==0
    {
        int sum = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (j % 2 == 0) sum += a[i][j];
        ans = max(ans, sum);
    }
    // Pattern B: fill (i,j) where j%2==1
    {
        int sum = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (j % 2 == 1) sum += a[i][j];
        ans = max(ans, sum);
    }
    // Pattern C: fill (i,j) where i%2==0
    {
        int sum = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i % 2 == 0) sum += a[i][j];
        ans = max(ans, sum);
    }
    // Pattern D: fill (i,j) where i%2==1
    {
        int sum = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i % 2 == 1) sum += a[i][j];
        ans = max(ans, sum);
    }
    // Pattern E: fill (i,j) where (i+j)%2==0
    {
        int sum = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if ((i + j) % 2 == 0) sum += a[i][j];
        ans = max(ans, sum);
    }
    // Pattern F: fill (i,j) where (i+j)%2==1
    {
        int sum = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if ((i + j) % 2 == 1) sum += a[i][j];
        ans = max(ans, sum);
    }
    
    cout << ans << endl;
    return 0;
}
