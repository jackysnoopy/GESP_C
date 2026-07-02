#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int Q;
    cin >> Q;
    
    while (Q--) {
        string S;
        cin >> S;
        
        string T = "";
        int left = 0, right = S.length() - 1;
        
        // 简单贪心：每次选择最小的字符
        while (left <= right) {
            if (S[left] <= S[right]) {
                T = S[left] + T;
                left++;
            } else {
                T = S[right] + T;
                right--;
            }
        }
        
        cout << T << "\n";
    }
    
    return 0;
}