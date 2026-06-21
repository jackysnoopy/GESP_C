#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

static char ibuf[1<<16];
static int ilen=0, ipos=0;
inline int gc(){
    if(ipos==ilen){ ilen=(int)fread(ibuf,1,sizeof(ibuf),stdin); ipos=0; if(ilen==0) return -1; }
    return ibuf[ipos++];
}
inline long long readInt(){
    int c=gc(); while(c!=-1 && c!='-' && (c<'0'||c>'9')) c=gc();
    if(c==-1) return -1;
    int neg=0; if(c=='-'){neg=1;c=gc();}
    long long x=0; while(c>='0'&&c<='9'){ x=x*10+(c-'0'); c=gc(); }
    return neg?-x:x;
}

struct BIT {
    int n, pw;
    vector<int> t;
    BIT(int n=0):n(n),t(n+2,0){
        pw=1; while(pw*2<=n) pw*=2;
    }
    inline void add(int i,int v){ for(++i; i<=n; i+=i&(-i)) t[i]+=v; }
    inline int findKth(int k){            // 0-based index of k-th present (k>=1)
        int pos=0;
        for(int step=pw; step>0; step>>=1){
            if(pos+step<=n && t[pos+step] < k){ k-=t[pos+step]; pos+=step; }
        }
        return pos;
    }
};

int main(){
    int n = (int)readInt();
    if(n<=0) return 0;
    int m = 2*n;
    vector<long long> F(m), B(m);
    for(int i=0;i<m;++i) F[i]=readInt();
    for(int i=0;i<m;++i) B[i]=readInt();
    vector<int> Q(n);
    for(int i=0;i<n;++i) Q[i]=(int)readInt();

    vector<int> byF(m), byB(m);
    for(int i=0;i<m;++i){ byF[i]=i; byB[i]=i; }
    sort(byF.begin(),byF.end(),[&](int x,int y){ return F[x]<F[y]; });
    sort(byB.begin(),byB.end(),[&](int x,int y){ return B[x]<B[y]; });
    vector<int> frank(m), brank(m);
    for(int r=0;r<m;++r){ frank[byF[r]]=r; brank[byB[r]]=r; }

    BIT bf(m), bb(m);
    for(int i=0;i<m;++i){ bf.add(i,1); bb.add(i,1); }
    int remF=m, remB=m;

    long long MF=0,MB=0,SF=0,SB=0;
    for(int rnd=0; rnd<n; ++rnd){
        if(Q[rnd]==1){
            int rmax = bf.findKth(remF);   // max F remaining
            int rmin = bf.findKth(1);      // min F remaining
            int idM = byF[rmax], idS = byF[rmin];
            MF += F[idM]; MB += B[idM];
            SF += F[idS]; SB += B[idS];
            bf.add(rmax,-1); bb.add(brank[idM],-1);
            bf.add(rmin,-1); bb.add(brank[idS],-1);
            remF-=2; remB-=2;
        } else {
            int rmax = bb.findKth(remB);   // max B remaining
            int rmin = bb.findKth(1);      // min B remaining
            int idM = byB[rmax], idS = byB[rmin];
            MF += F[idM]; MB += B[idM];
            SF += F[idS]; SB += B[idS];
            bb.add(rmax,-1); bf.add(frank[idM],-1);
            bb.add(rmin,-1); bf.add(frank[idS],-1);
            remF-=2; remB-=2;
        }
    }
    printf("%lld %lld\n%lld %lld\n", MF, MB, SF, SB);
    return 0;
}
