#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int R, C;
    int cs = 0;
    while (cin >> R >> C && R) {
        vector<string> grid(R);
        for (int i = 0; i < R; ++i) cin >> grid[i];
        int sr=-1,sc=-1,br=-1,bc=-1,tr=-1,tc=-1;
        for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) {
            if (grid[i][j]=='@'){sr=i;sc=j;}
            else if (grid[i][j]=='$'){br=i;bc=j;}
            else if (grid[i][j]=='.'){tr=i;tc=j;}
        }
        auto ok=[&](int r,int c){return r>=0&&r<R&&c>=0&&c<C&&grid[r][c]!='#';};
        int sc2=sr*C+sc, sb=br*C+bc;
        vector<vector<int>> dist(R*C, vector<int>(R*C, -1));
        queue<tuple<int,int,int>> q;
        dist[sc2][sb]=0;
        q.emplace(sc2, sb, 0);
        const int dr[]={-1,1,0,0},dc[]={0,0,-1,1};
        int ans=-1;
        while(!q.empty()){
            auto [ps,bs,d]=q.front();q.pop();
            if(bs==tr*C+tc){ans=d;break;}
            int pr=ps/C,pc=ps%C,br2=bs/C,bc2=bs%C;
            for(int dir=0;dir<4;++dir){
                int npr=pr+dr[dir],npc=pc+dc[dir];
                if(!ok(npr,npc))continue;
                if(npr==br2&&npc==bc2){
                    int nbr=br2+dr[dir],nbc=bc2+dc[dir];
                    if(!ok(nbr,nbc))continue;
                    int nbs=nbr*C+nbc,nps=npr*C+npc;
                    if(dist[nps][nbs]==-1){dist[nps][nbs]=d+1;q.emplace(nps,nbs,d+1);}
                }else{
                    int nps=npr*C+npc;
                    if(dist[nps][bs]==-1){dist[nps][bs]=d+1;q.emplace(nps,bs,d+1);}
                }
            }
        }
        cout<<"Maze #"<<++cs<<'\n';
        if(ans==-1)cout<<"Impossible.\n\n";
        else cout<<ans<<"\n\n";
    }
    return 0;
}
