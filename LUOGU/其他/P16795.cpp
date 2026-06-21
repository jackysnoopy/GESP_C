#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    string s;
    cin >> s;
    // c[i] = 0 means |p[i]-p[i+1]| is even (same parity)
    // c[i] = 1 means |p[i]-p[i+1]| is odd (different parity)
    // We need to construct a permutation 1..n matching the parity constraints.
    // Lexicographically smallest.
    //
    // Key: adjacent elements must have same or different parity.
    // Odd numbers: 1,3,5,... count = (n+1)/2
    // Even numbers: 2,4,6,... count = n/2
    //
    // At each position, we need to choose a number with specific parity.
    // c[i]='0': p[i] and p[i+1] same parity
    // c[i]='1': p[i] and p[i+1] different parity
    //
    // This defines parity transitions. Position 1 has some parity.
    // From position 1, the parity of each position is determined by the transitions.
    // If c[0]='0': same parity. If c[0]='1': different.
    //
    // We need to check both possibilities for position 1 (odd or even) and pick the one
    // that works and gives lexicographically smallest result.
    
    vector<int> ans(n, 0);
    bool possible = false;
    
    for (int startParity = 0; startParity <= 1; startParity++) {
        // Determine required parity for each position
        vector<int> reqParity(n);
        reqParity[0] = startParity;
        for (int i = 0; i < n - 1; i++) {
            if (s[i] == '0') reqParity[i+1] = reqParity[i];
            else reqParity[i+1] = 1 - reqParity[i];
        }
        // Count how many positions need odd/even
        int needOdd = 0, needEven = 0;
        for (int i = 0; i < n; i++) {
            if (reqParity[i] == 1) needOdd++;
            else needEven++;
        }
        int availOdd = (n + 1) / 2;
        int availEven = n / 2;
        if (needOdd > availOdd || needEven > availEven) continue;
        
        // Construct lexicographically smallest permutation
        vector<int> oddNums, evenNums;
        for (int i = 1; i <= n; i++) {
            if (i % 2 == 1) oddNums.push_back(i);
            else evenNums.push_back(i);
        }
        vector<int> candidate(n);
        int oi = 0, ei = 0;
        for (int i = 0; i < n; i++) {
            if (reqParity[i] == 1) candidate[i] = oddNums[oi++];
            else candidate[i] = evenNums[ei++];
        }
        if (!possible || candidate < ans) {
            ans = candidate;
            possible = true;
        }
    }
    
    if (!possible) { cout << -1 << "\n"; return 0; }
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << ans[i];
    }
    cout << "\n";
    return 0;
}
