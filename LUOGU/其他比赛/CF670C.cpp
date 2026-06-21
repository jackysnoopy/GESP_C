#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        int lang;
        cin >> lang;
        cnt[lang]++;
    }
    
    int m;
    cin >> m;
    vector<int> audio(m), sub(m);
    for (int i = 0; i < m; i++) cin >> audio[i];
    for (int i = 0; i < m; i++) cin >> sub[i];
    
    int best_idx = 0, best_audio = -1, best_sub = -1;
    for (int i = 0; i < m; i++) {
        int a = cnt[audio[i]];
        int s = cnt[sub[i]];
        if (a > best_audio || (a == best_audio && s > best_sub)) {
            best_audio = a;
            best_sub = s;
            best_idx = i + 1;
        }
    }
    
    cout << best_idx << "\n";
    return 0;
}