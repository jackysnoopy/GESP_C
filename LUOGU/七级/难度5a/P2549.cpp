#include <bits/stdc++.h>
using namespace std;

string wordToNum(string word) {
    string res = "";
    for (char c : word) {
        if (c == 'A' || c == 'B') res += '2';
        else if (c == 'C' || c == 'D') res += '2';
        else if (c == 'E' || c == 'F') res += '3';
        else if (c == 'G' || c == 'H') res += '4';
        else if (c == 'I' || c == 'J') res += '4';
        else if (c == 'K' || c == 'L') res += '5';
        else if (c == 'M' || c == 'N') res += '6';
        else if (c == 'O' || c == 'P') res += '6';
        else if (c == 'Q' || c == 'R' || c == 'S') res += '7';
        else if (c == 'T' || c == 'U') res += '8';
        else if (c == 'V' || c == 'W') res += '8';
        else if (c == 'X' || c == 'Y' || c == 'Z') res += '9';
    }
    return res;
}

int main() {
    int D, N;
    scanf("%d%d", &D, &N);
    
    vector<pair<string, int>> words;
    for (int i = 0; i < N; i++) {
        string word;
        cin >> word;
        string num = wordToNum(word);
        if (num.size() <= D) {
            words.push_back({num, (int)num.size()});
        }
    }
    
    sort(words.begin(), words.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        if (a.first.size() != b.first.size()) return a.first.size() > b.first.size();
        return a.first > b.first;
    });
    
    string result = "";
    int remaining = D;
    
    for (auto& p : words) {
        if (p.second <= remaining) {
            result += p.first;
            remaining -= p.second;
        }
    }
    
    if (result.empty()) {
        cout << "0" << endl;
    } else {
        cout << result << endl;
    }
    
    return 0;
}
