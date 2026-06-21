#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int id, win;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    vector<vector<char>> mat(N, vector<char>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> mat[i][j];
    
    vector<Node> nodes(N);
    for (int i = 0; i < N; i++) {
        nodes[i].id = i + 1;
        nodes[i].win = 0;
        for (int j = 0; j < N; j++)
            if (mat[i][j] == 'W') nodes[i].win++;
    }
    
    sort(nodes.begin(), nodes.end(), [](const Node& a, const Node& b) {
        return a.win > b.win;
    });
    
    int k = N / 2;
    cout << nodes[k].id << "\n";
    return 0;
}