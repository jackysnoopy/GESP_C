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
        string s;
        cin >> s;
        int len = s.size();
        int upper = 0;
        for (char c : s) if (c >= 'A' && c <= 'Z') upper++;
        
        // "五字神人": length == 5 OR upper == 5.
        // Operations:
        // 1. Delete a character
        // 2. Change a character's case
        // 3. Append a lowercase letter
        
        // Want min operations to make length==5 OR upper==5.
        
        // Case 1: Make length == 5.
        //   If len == 5: 0 ops (regardless of upper).
        //   If len < 5: append (5 - len) lowercase letters. Cost = 5 - len.
        //   If len > 5: delete (len - 5) characters. Cost = len - 5.
        //   Note: we can choose which to delete, and we might want to keep uppercase.
        //   But cost is just len - 5 regardless.
        
        // Case 2: Make upper == 5.
        //   Need 5 uppercase letters. 
        //   Current: upper uppercase, len - upper lowercase.
        //   Options:
        //   - Convert lowercase to uppercase: cost = max(0, 5 - upper) per conversion.
        //     But we also need len >= 5 (can't have 5 uppercase if len < 5).
        //     If len < 5: first append (5 - len) lowercase, then convert some.
        //       Total = (5 - len) + max(0, 5 - upper).
        //       Wait, after appending, upper is still the same, but len becomes 5.
        //       Need to convert 5 - upper of the lowercase to uppercase.
        //       Cost = (5 - len) + (5 - upper).
        //     If len >= 5: cost = max(0, 5 - upper).
        //       But if upper > 5: need to convert some uppercase to lowercase first!
        //       Cost = (upper - 5) + (5 - upper) = 0? No.
        //       If upper >= 5: convert (upper - 5) uppercase to lowercase. Cost = upper - 5.
        //         Then upper becomes 5. Done.
        //       If upper < 5: convert (5 - upper) lowercase to uppercase. Cost = 5 - upper.
        //         But need len >= 5 to have enough characters.
        //       If len < 5 and upper < 5: append + convert. Cost = (5-len) + (5-upper).
        //       If len < 5 and upper >= 5: convert (upper-5) to lowercase. Cost = upper - 5.
        //         Wait, but len < 5 means we have fewer than 5 characters, so upper <= len < 5.
        //         So upper < 5 always when len < 5.
        
        // Let me compute both costs and take min.
        int cost1, cost2;
        
        // Case 1: make length == 5
        if (len <= 5) {
            cost1 = 5 - len;
        } else {
            cost1 = len - 5;
        }
        
        // Case 2: make upper == 5
        if (len >= 5) {
            if (upper >= 5) {
                cost2 = upper - 5;
            } else {
                cost2 = 5 - upper;
            }
        } else {
            // len < 5: need to append (5-len) chars, then convert (5-upper) to uppercase
            cost2 = (5 - len) + (5 - upper);
        }
        
        cout << min(cost1, cost2) << "\n";
    }
    return 0;
}
