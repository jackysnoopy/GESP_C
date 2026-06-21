#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    
    vector<int> queries(q);
    for (int i = 0; i < q; i++) cin >> queries[i];
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = s[i] - '0';
    
    auto isSingleton = [&](int pos) -> bool {
        if (pos < 0 || pos >= n || arr[pos] != 1) return false;
        bool left = (pos > 0 && arr[pos-1] == 1);
        bool right = (pos < n-1 && arr[pos+1] == 1);
        return !left && !right;
    };
    
    auto isBlock = [&](int pos) -> bool {
        if (pos < 0 || pos >= n || arr[pos] != 1) return false;
        return !isSingleton(pos);
    };
    
    auto getGain = [&](int pos) -> int {
        if (arr[pos] != 0) return -1;
        int singN = 0, blockN = 0;
        if (pos > 0 && arr[pos-1] == 1) {
            if (isSingleton(pos-1)) singN++; else blockN++;
        }
        if (pos < n-1 && arr[pos+1] == 1) {
            if (isSingleton(pos+1)) singN++; else blockN++;
        }
        if (singN + blockN == 0) return 0;
        return singN + 1;
    };
    
    struct Entry {
        int gain, pos;
        bool operator<(const Entry& o) const {
            if (gain != o.gain) return gain > o.gain;
            return pos < o.pos;
        }
    };
    set<Entry> pq;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            pq.insert({getGain(i), i});
        }
    }
    
    // Track answer incrementally
    int curAnswer = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1 && ((i > 0 && arr[i-1] == 1) || (i < n-1 && arr[i+1] == 1))) {
            curAnswer++;
        }
    }
    
    vector<int> answers(n + 1);
    answers[0] = curAnswer;
    
    auto updatePos = [&](int pos) {
        if (pos >= 0 && pos < n && arr[pos] == 0) {
            int oldGain = getGain(pos); // current gain
            // Remove old entry, insert new
            pq.erase({oldGain, pos}); // might not find if gain changed
            pq.insert({getGain(pos), pos});
        }
    };
    
    for (int k = 1; k <= n; k++) {
        int bestPos = -1;
        
        while (!pq.empty()) {
            auto it = pq.begin();
            if (arr[it->pos] != 0) { pq.erase(it); continue; }
            int g = getGain(it->pos);
            if (g != it->gain) { pq.erase(it); pq.insert({g, it->pos}); continue; }
            bestPos = it->pos;
            pq.erase(it);
            break;
        }
        
        if (bestPos == -1) {
            for (int i = 0; i < n; i++) {
                if (arr[i] == 0) { bestPos = i; break; }
            }
            if (bestPos == -1) { answers[k] = answers[k-1]; continue; }
        }
        
        int gain = getGain(bestPos);
        arr[bestPos] = 1;
        curAnswer += gain;
        
        updatePos(bestPos - 1);
        updatePos(bestPos + 1);
        
        answers[k] = curAnswer;
    }
    
    for (int i = 0; i < q; i++) {
        cout << answers[queries[i]] << "\n";
    }
    
    return 0;
}
