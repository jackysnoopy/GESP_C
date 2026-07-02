#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

string toLower(const string& s) {
    string res = s;
    for (auto& c : res) c = tolower(c);
    return res;
}

string toUpper(const string& s) {
    string res = s;
    for (auto& c : res) c = toupper(c);
    return res;
}

struct Match {
    int pos;
    int len;
    string keyword;
    bool operator<(const Match& o) const { return pos < o.pos; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    vector<string> keywords;
    bool firstCase = true;

    while (getline(cin, line)) {
        if (line == "#") break;

        if (line.empty() || line.back() == ':') {
            if (!line.empty() && line.back() == ':')
                line.pop_back();
            if (!line.empty())
                keywords.push_back(line);
            if (line.empty()) {
                if (!firstCase) cout << "\n";
                firstCase = false;

                vector<string> text;
                string tl;
                while (getline(cin, tl) && tl != "#") {
                    text.push_back(tl);
                }

                string full;
                vector<int> lineStart;
                for (int i = 0; i < (int)text.size(); i++) {
                    lineStart.push_back((int)full.size());
                    full += text[i] + "\n";
                }

                string lowerFull = toLower(full);
                vector<Match> matches;

                for (auto& kw : keywords) {
                    string lk = toLower(kw);
                    size_t pos = 0;
                    while ((pos = lowerFull.find(lk, pos)) != string::npos) {
                        matches.push_back({(int)pos, (int)lk.size(), kw});
                        pos += lk.size();
                    }
                }

                sort(matches.begin(), matches.end());

                vector<Match> result;
                int lastEnd = -1;
                for (auto& m : matches) {
                    if (m.pos >= lastEnd) {
                        result.push_back(m);
                        lastEnd = m.pos + m.len;
                    }
                }

                for (auto& m : result) {
                    int ctxStart = max(0, m.pos - 5);
                    int ctxEnd = min((int)full.size(), m.pos + m.len + 5);
                    string prefix = full.substr(ctxStart, m.pos - ctxStart);
                    string suffix = full.substr(m.pos + m.len, ctxEnd - m.pos - m.len);

                    for (int i = 0; i < (int)prefix.size(); i++) {
                        if (prefix[i] != '\n') cout << prefix[i];
                        else cout << " ";
                    }
                    cout << toUpper(m.keyword);
                    for (int i = 0; i < (int)suffix.size(); i++) {
                        if (suffix[i] != '\n') cout << suffix[i];
                        else cout << " ";
                    }
                    cout << "\n";
                }

                keywords.clear();
                break;
            }
        }
    }

    return 0;
}
