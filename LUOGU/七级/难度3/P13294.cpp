#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <algorithm>
using namespace std;

const long long MOD = 1000002013;
const long long INV2 = (MOD + 1) / 2;   // 2 * INV2 == 1 (mod MOD), MOD is odd

// fare for travelling d stops on a line of N stations:
//   d*N - d*(d-1)/2   (taken mod MOD)
long long cost(long long d, long long N){
    long long a = (d % MOD) * (N % MOD) % MOD;
    long long b = (d % MOD) * ((d - 1) % MOD) % MOD;
    b = b * INV2 % MOD;
    long long res = (a - b) % MOD;
    if(res < 0) res += MOD;
    return res;
}

int main(){
    int T; cin >> T;
    for(int tc=1; tc<=T; ++tc){
        long long N; int M;
        cin >> N >> M;
        // events grouped by station: origins added, destinations removed
        map<long long, pair<long long,long long>> ev;
        long long normal = 0;
        for(int i=0; i<M; ++i){
            long long o, e, p;
            cin >> o >> e >> p;
            normal = (normal + cost(e - o, N) * (p % MOD)) % MOD;
            ev[o].first  += p;   // entry cards picked up at o
            ev[e].second += p;   // entry cards surrendered at e
        }
        // pool of currently held entry cards: origin station -> count
        map<long long,long long> pool;
        long long actual = 0;
        for(auto &pr : ev){
            long long s = pr.first;
            long long addOrig = pr.second.first;
            long long remDest = pr.second.second;
            if(addOrig > 0) pool[s] += addOrig;     // entries happen first
            long long need = remDest;
            while(need > 0){
                auto it = pool.rbegin();            // surrender closest (largest) origin
                long long o = it->first;
                long long cnt = it->second;
                long long take = min(need, cnt);
                actual = (actual + cost(s - o, N) * (take % MOD)) % MOD;
                need -= take;
                cnt -= take;
                if(cnt == 0) pool.erase(o);
                else pool[o] = cnt;
            }
        }
        long long loss = (normal - actual) % MOD;
        if(loss < 0) loss += MOD;
        cout << "Case #" << tc << ": " << loss << "\n";
    }
    return 0;
}
