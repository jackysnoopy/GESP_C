#include <iostream>
#include <string>
#include <stack>
#include <cctype>
using namespace std;

int main() {
    string line;
    while (getline(cin, line)) {
        stack<string> wordStack;
        string numStr;
        
        for (char c : line) {
            if (isdigit(c)) {
                numStr += c;
            } else {
                if (!numStr.empty()) {
                    int len = stoi(numStr);
                    string word;
                    for (int i = 0; i < len; i++) {
                        char ch;
                        cin.get(ch);
                        word += ch;
                    }
                    wordStack.push(word);
                    numStr.clear();
                }
                string s(1, c);
                wordStack.push(s);
            }
        }
        if (!numStr.empty()) {
            int len = stoi(numStr);
            string word;
            for (int i = 0; i < len; i++) {
                char ch;
                cin.get(ch);
                word += ch;
            }
            wordStack.push(word);
        }
        
        string result;
        while (!wordStack.empty()) {
            result = wordStack.top() + result;
            wordStack.pop();
        }
        
        cout << result << endl;
    }
    return 0;
}
