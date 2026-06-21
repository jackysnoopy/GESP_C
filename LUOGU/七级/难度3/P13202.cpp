#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    int T; cin >> T;
    for(int t=1; t<=T; ++t){
        string s; cin >> s;
        int n = (int)s.size();
        // Each pair's best value is 10 if the two days share a mood, else 5.
        // Total = 5*L + 5*(#same-mood pairs). Maximize same-mood non-crossing pairs.
        // Equivalent to free-group reduction: cancel adjacent equal letters;
        // #cancellations is invariant and equals the maximum.
        vector<char> st;
        long long same = 0;
        for(char c : s){
            if(!st.empty() && st.back()==c){
                st.pop_back();
                ++same;
            } else {
                st.push_back(c);
            }
        }
        long long L = n/2;
        long long ans = 5*L + 5*same;
        cout << "Case #" << t << ": " << ans << "\n";
    }
    return 0;
}
