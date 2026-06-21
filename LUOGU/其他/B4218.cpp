#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    
    vector<char> stk;
    int answer = 0;
    
    for (char c : s) {
        stk.push_back(c);
        // Check from the top, replacing ABC with BCA
        int checkPos = (int)stk.size() - 3;
        while (checkPos >= 0) {
            if (stk[checkPos] == 'A' && stk[checkPos+1] == 'B' && stk[checkPos+2] == 'C') {
                // Replace ABC with BCA
                stk[checkPos] = 'B';
                stk[checkPos+1] = 'C';
                stk[checkPos+2] = 'A';
                answer++;
                checkPos--; // Check one position to the left
            } else {
                break;
            }
        }
    }
    
    cout << answer << "\n";
    return 0;
}
