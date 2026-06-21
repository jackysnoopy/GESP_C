#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    long long A, B;
    cin >> N >> A >> B;
    
    map<long long, long long> cnt;
    for (int i = 0; i < N; i++) {
        long long d, n;
        cin >> n >> d;
        cnt[d] = n;
    }
    
    long long ans = 0;
    
    // 自配对
    for (map<long long, long long>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
        long long d = it->first;
        long long& c = it->second;
        if (2 * d == A) {
            ans += c / 2;
            c %= 2;
        }
        if (2 * d == B && A != B) {
            ans += c / 2;
            c %= 2;
        }
    }
    
    // 尝试两种顺序：先A后B，先B后A，取最优
    long long best = 0;
    
    for (int order = 0; order < 2; order++) {
        map<long long, long long> tmp = cnt;
        long long cur = ans;
        
        vector<long long> targets;
        if (order == 0) { targets.push_back(A); targets.push_back(B); }
        else { targets.push_back(B); targets.push_back(A); }
        
        // 去重
        if (A == B) targets.resize(1);
        
        for (int ti = 0; ti < (int)targets.size(); ti++) {
            long long T = targets[ti];
            for (map<long long, long long>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
                long long d = it->first;
                if (d * 2 > T) break;
                long long need = T - d;
                if (need == d) continue;
                map<long long, long long>::iterator jt = tmp.find(need);
                if (jt != tmp.end() && jt->second > 0 && it->second > 0) {
                    long long pairs = min(it->second, jt->second);
                    cur += pairs;
                    it->second -= pairs;
                    jt->second -= pairs;
                }
            }
        }
        
        best = max(best, cur);
    }
    
    cout << best << endl;
    return 0;
}
