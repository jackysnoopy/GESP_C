#include <iostream>
#include <string>
#include <queue>
#include <set>
using namespace std;

struct State {
    string s;
    int steps;
};

string removePairs(const string& s) {
    string result;
    for (char c : s) {
        if (!result.empty() && result.back() == c)
            result.pop_back();
        else
            result.push_back(c);
    }
    return result;
}

int main() {
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        string s;
        cin >> s;
        
        if (t > 0) cout << endl;
        
        string result = removePairs(s);
        cout << result.length() << endl;
    }
    return 0;
}
