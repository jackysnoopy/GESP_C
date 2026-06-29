#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

bool canFormGraph(vector<int>& degrees, int exclude) {
    int n = degrees.size();
    vector<int> remaining;
    for (int i = 0; i < n; i++) {
        if (i != exclude) {
            remaining.push_back(degrees[i]);
        }
    }
    
    int sum = accumulate(remaining.begin(), remaining.end(), 0);
    if (sum % 2 != 0) return false;
    
    sort(remaining.begin(), remaining.end(), greater<int>());
    
    // Check if the sequence is graphical using Erdős–Gallai theorem
    int total = sum;
    for (int i = 0; i < remaining.size(); i++) {
        if (remaining[i] < 0) return false;
        total -= remaining[i];
        int remaining_count = remaining.size() - i - 1;
        if (total < 0) return false;
    }
    
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> degrees(n + 1);
    for (int i = 0; i <= n; i++) {
        cin >> degrees[i];
    }
    
    vector<int> valid;
    for (int i = 0; i <= n; i++) {
        if (canFormGraph(degrees, i)) {
            valid.push_back(i + 1);
        }
    }
    
    cout << valid.size() << "\n";
    for (int x : valid) {
        cout << x << "\n";
    }
    
    return 0;
}
