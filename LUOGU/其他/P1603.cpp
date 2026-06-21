#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    getline(cin, line);
    string norm[] = {"zero","one","two","three","four","five","six","seven","eight","nine",
                      "ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen",
                      "seventeen","eighteen","nineteen","twenty"};
    int nval[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    string irreg[] = {"both","another","first","second","third"};
    int ival[] = {2,1,1,2,3};
    stringstream ss(line);
    string word;
    vector<int> digits;
    while (ss >> word) {
        if (word == ".") break;
        for (size_t i = 0; i < word.size(); i++)
            if (word[i] >= 'A' && word[i] <= 'Z') word[i] = word[i] - 'A' + 'a';
        bool found = false;
        for (int i = 0; i < 21; i++) {
            if (word == norm[i]) { digits.push_back(nval[i]); found = true; break; }
        }
        if (!found) {
            for (int i = 0; i < 5; i++) {
                if (word == irreg[i]) { digits.push_back(ival[i]); found = true; break; }
            }
        }
    }
    if (digits.empty()) { cout << 0 << "\n"; return 0; }
    vector<string> parts;
    for (size_t d = 0; d < digits.size(); d++) {
        int sq = (digits[d] * digits[d]) % 100;
        string s = "";
        s += (char)('0' + sq / 10);
        s += (char)('0' + sq % 10);
        parts.push_back(s);
    }
    sort(parts.begin(), parts.end());
    string result = "";
    for (size_t i = 0; i < parts.size(); i++) result += parts[i];
    size_t start = 0;
    while (start < result.size() && result[start] == '0') start++;
    if (start == result.size()) cout << 0 << "\n";
    else cout << result.substr(start) << "\n";
    return 0;
}
