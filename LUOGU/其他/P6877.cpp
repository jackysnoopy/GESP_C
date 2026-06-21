#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n+1), b(n);
    for (int i = 0; i < n+1; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    // For each k (boss removes tie k), assign remaining n ties to n employees
    // Minimize max(a[assigned] - b[employee])
    // Sort b ascending. For remaining ties, sort ascending.
    // Greedy: assign smallest available tie to smallest b.
    
    // Pre-sort
    vector<int> sorted_b = b;
    sort(sorted_b.begin(), sorted_b.end());
    
    for (int k = 0; k < n+1; k++) {
        vector<int> ties;
        for (int i = 0; i < n+1; i++)
            if (i != k) ties.push_back(a[i]);
        sort(ties.begin(), ties.end());
        // Greedy match: ties[i] to sorted_b[i]
        int worst = 0;
        for (int i = 0; i < n; i++)
            worst = max(worst, ties[i] - sorted_b[i]);
        cout << max(0, worst) << (k < n ? " " : "\n");
    }
    return 0;
}
