#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
static char buf[1<<21],*p1=buf,*p2=buf;
inline int gc(){return (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++);}
inline ll readInt(){
    int c=gc(); while(c!='-'&&(c<'0'||c>'9')) c=gc();
    int s=1; if(c=='-'){s=-1;c=gc();}
    ll x=0; while(c>='0'&&c<='9'){x=x*10+(c-'0');c=gc();}
    return x*s;
}
int parent[10000061];
int findr(int x){ while(parent[x]!=x){ parent[x]=parent[parent[x]]; x=parent[x]; } return x; }
void unite(int a,int b){ a=findr(a); b=findr(b); if(a!=b) parent[b]=a; }
int main(){
    int n=(int)readInt();
    int B=60;
    int tot=n+B;
    for(int i=0;i<tot;i++) parent[i]=i;
    for(int i=0;i<n;i++){
        ll v=readInt();
        if(v==0) continue;
        while(v){
            int b=__builtin_ctzll(v);
            v&=(v-1);
            unite(i, n+b);
        }
    }
    vector<char> seen(tot,0);
    int ans=0;
    for(int i=0;i<n;i++){
        int r=findr(i);
        if(!seen[r]){ seen[r]=1; ans++; }
    }
    printf("%d\n",ans);
    return 0;
}
