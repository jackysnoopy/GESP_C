#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        char piece;
        int r, c;
        cin >> piece >> r >> c;
        
        int ans = 0;
        switch (piece) {
            case 'r':
                ans = min(r, c);
                break;
            case 'Q':
                ans = min(r, c);
                break;
            case 'k':
                ans = (r * c + 1) / 2;
                break;
            case 'K':
                ans = ((r + 1) / 2) * ((c + 1) / 2);
                break;
        }
        cout << ans << "\n";
    }
    return 0;
}
