#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        string s;
        cin >> n >> s;
        
        int count = 0;
        for (char c : s) {
            if (c == '1') count++;
        }
        
        if (count == 0) {
            cout << "0\n";
        } else if (count == 1) {
            cout << "1\n";
        } else {
            cout << "1";
            for (int i = 0; i < count - 1; i++) {
                cout << "0";
            }
            cout << "\n";
        }
    }
    
    return 0;
}