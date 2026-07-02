#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string line;
    while (getline(cin, line)) {
        int up = 0, down = 0;
        bool possible = true;
        
        for (char c : line) {
            if (c == 'U') {
                up++;
            } else {
                down++;
            }
            if (down > up) {
                possible = false;
                break;
            }
        }
        
        if (up != down) possible = false;
        
        if (possible) {
            cout << "Possible\n";
        } else {
            cout << "Impossible\n";
        }
    }
    return 0;
}
