#include <iostream>
#include <string>
using namespace std;

int min_rep(const string& s) {
    int n = s.size(), i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        int diff = s[(i+k)%n] - s[(j+k)%n];
        if (diff == 0) k++;
        else {
            if (diff > 0) i += k + 1;
            else j += k + 1;
            if (i == j) j++;
            k = 0;
        }
    }
    return min(i, j);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string a, b;
    while (cin >> a >> b) {
        if (a.size() != b.size()) { cout << "No\n"; continue; }
        int pa = min_rep(a), pb = min_rep(b);
        int n = a.size();
        bool same = true;
        for (int i = 0; i < n; i++)
            if (a[(pa+i)%n] != b[(pb+i)%n]) { same = false; break; }
        cout << (same ? "Yes" : "No") << "\n";
    }
    return 0;
}