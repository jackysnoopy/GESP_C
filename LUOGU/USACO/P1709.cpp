#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    string s;
    cin >> s;
    // Find minimum rotation using Booth's algorithm
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        int diff = s[(i+k)%n] - s[(j+k)%n];
        if (diff == 0) k++;
        else {
            if (diff > 0) i = i + k + 1;
            else j = j + k + 1;
            if (i == j) j++;
            k = 0;
        }
    }
    int pos = min(i, j);
    cout << pos << endl;
    return 0;
}