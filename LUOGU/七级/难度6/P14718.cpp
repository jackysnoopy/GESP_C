#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    // Read triangular matrix
    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            cin >> A[i][j];
        }
    }
    
    // Greedy: at each diagonal position (i,i), choose the maximum value
    // in the rectangular region [i..N-1][0..i]
    
    long long answer = 0;
    vector<int> solution(N);
    
    for (int i = 0; i < N; i++) {
        // Find maximum in region [i..N-1][0..i]
        int maxVal = 0;
        int maxR = i, maxC = 0;
        
        for (int r = i; r < N; r++) {
            for (int c = 0; c <= i; c++) {
                if (A[r][c] > maxVal) {
                    maxVal = A[r][c];
                    maxR = r;
                    maxC = c;
                }
            }
        }
        
        answer += maxVal;
        solution[i] = maxVal;
        
        // Mark this cell as used
        A[maxR][maxC] = 0;
    }
    
    cout << answer << "\n";
    for (int i = 0; i < N; i++) {
        cout << solution[i] << (i + 1 < N ? " " : "\n");
    }
    
    return 0;
}
