#include <cstdio>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        scanf("%d", &n);
        vector<vector<int>> X(n, vector<int>(n));
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                scanf("%d", &X[i][j]);
        vector<int> badRows, badCols;
        vector<char> rowBad(n,0), colBad(n,0);
        for(int i=0;i<n;i++){
            vector<char> seen(n+1,0);
            bool perm = true;
            for(int j=0;j<n;j++){
                if(seen[X[i][j]]){ perm=false; break; }
                seen[X[i][j]]=1;
            }
            if(perm){ badRows.push_back(i); rowBad[i]=1; }
        }
        for(int j=0;j<n;j++){
            vector<char> seen(n+1,0);
            bool perm = true;
            for(int i=0;i<n;i++){
                if(seen[X[i][j]]){ perm=false; break; }
                seen[X[i][j]]=1;
            }
            if(perm){ badCols.push_back(j); colBad[j]=1; }
        }
        int a = (int)badRows.size(), b = (int)badCols.size();
        int m = max(a, b);
        vector<int> goodRows, goodCols;
        for(int i=0;i<n;i++) if(!rowBad[i]) goodRows.push_back(i);
        for(int j=0;j<n;j++) if(!colBad[j]) goodCols.push_back(j);

        vector<array<int,3>> ops;
        int pairs = min(a, b);
        for(int k=0;k<pairs;k++){
            int i = badRows[k], j = badCols[k];
            int v = X[i][j];
            int w = v % n + 1;
            ops.push_back({i+1, j+1, w});
        }
        if(a > b){
            int gi = 0;
            for(int k=b;k<a;k++){
                int i = badRows[k];
                int j = goodCols[gi++];
                int v = X[i][j];
                int w = -1;
                for(int r=0;r<n;r++){
                    if(r==i) continue;
                    if(X[r][j] != v){ w = X[r][j]; break; }
                }
                if(w == -1) w = v % n + 1;
                ops.push_back({i+1, j+1, w});
            }
        } else if(b > a){
            int ri = 0;
            for(int k=a;k<b;k++){
                int j = badCols[k];
                int i = goodRows[ri++];
                int v = X[i][j];
                int w = -1;
                for(int c=0;c<n;c++){
                    if(c==j) continue;
                    if(X[i][c] != v){ w = X[i][c]; break; }
                }
                if(w == -1) w = v % n + 1;
                ops.push_back({i+1, j+1, w});
            }
        }
        printf("%d\n", m);
        for(auto &op: ops){
            printf("%d %d %d\n", op[0], op[1], op[2]);
        }
    }
    return 0;
}
