#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXB=41005;
int N,B;
int Kb[25],Pb[25],Ab[25];
int skill[25][25];
int gtab[25][MAXB]; // gtab[j][base] = base + chain bonus additions for step j (1-indexed count)
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    if(!(cin>>N>>B)) return 0;
    for(int i=0;i<B;i++) cin>>Kb[i]>>Pb[i]>>Ab[i];
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) cin>>skill[i][j];
    // precompute gtab[j][base] for j=1..N
    for(int j=1;j<=N;j++){
        vector<int> idx;
        for(int i=0;i<B;i++) if(Kb[i]==j) idx.push_back(i);
        sort(idx.begin(),idx.end(),[](int a,int b){return Pb[a]<Pb[b];});
        for(int base=0;base<MAXB;base++){
            long long cur=base;
            for(int i:idx){ if(Pb[i]<=cur) cur+=Ab[i]; }
            gtab[j][base]=(cur<MAXB?(int)cur:MAXB-1);
        }
    }
    vector<int> dp(1<<N, -1);
    dp[0]=0;
    int full=(1<<N)-1;
    for(int mask=0;mask<(1<<N);mask++){
        if(dp[mask]<0) continue;
        int c=__builtin_popcount(mask); // events assigned = current 1-indexed count
        if(c==N) continue;
        int ev=c; // 0-indexed next event
        int step=c+1; // 1-indexed count after this assignment
        for(int cow=0;cow<N;cow++){
            if(mask>>cow&1) continue;
            int nmask=mask|(1<<cow);
            int base=dp[mask]+skill[cow][ev];
            int val;
            if(base>=MAXB) val=gtab[step][MAXB-1];
            else val=gtab[step][base];
            if(val>dp[nmask]) dp[nmask]=val;
        }
    }
    cout<<dp[full]<<"\n";
    return 0;
}
