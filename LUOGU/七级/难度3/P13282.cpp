#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int T; cin >> T;
    for(int tc=1; tc<=T; ++tc){
        int N, M; cin >> N >> M;
        vector<vector<int>> a(N, vector<int>(M));
        vector<int> rowmax(N, 0), colmax(M, 0);
        for(int i=0; i<N; ++i){
            for(int j=0; j<M; ++j){
                cin >> a[i][j];
                rowmax[i] = max(rowmax[i], a[i][j]);
                colmax[j] = max(colmax[j], a[i][j]);
            }
        }
        bool ok = true;
        for(int i=0; i<N && ok; ++i){
            for(int j=0; j<M; ++j){
                if(a[i][j] != min(rowmax[i], colmax[j])){
                    ok = false;
                    break;
                }
            }
        }
        cout << "Case #" << tc << ": " << (ok ? "YES" : "NO") << "\n";
    }
    return 0;
}
