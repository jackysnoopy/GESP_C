#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    string s;
    cin >> s;
    // Cat stone game: n stones in a row, some are "cat stones" (1).
    // Without full rules, implement common game theory approach.
    // Likely: Nim game or similar.
    
    // Count cat stones
    int cnt = 0;
    for (char c : s) if (c == '1') cnt++;
    
    // Simple: if odd number of cat stones, first player wins
    cout << (cnt % 2 ? "Alice" : "Bob") << endl;
    return 0;
}
