// UVA131 - Jugs (水罐问题)
// BFS搜索最短操作序列
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <string>
using namespace std;

struct State {
    int a, b;
    string ops;
};

int main() {
    int A, B, D;
    while (cin >> A >> B >> D) {
        queue<State> q;
        map<pair<int,int>, bool> visited;
        q.push({0, 0, ""});
        visited[{0, 0}] = true;
        while (!q.empty()) {
            State cur = q.front(); q.pop();
            if (cur.b == D) {
                cout << cur.ops;
                break;
            }
            // 六种操作：fill A, fill B, empty A, empty B, pour A->B, pour B->A
            if (cur.a < A && !visited[{A, cur.b}]) {
                visited[{A, cur.b}] = true;
                q.push({A, cur.b, cur.ops + "fill A\n"});
            }
            if (cur.b < B && !visited[{cur.a, B}]) {
                visited[{cur.a, B}] = true;
                q.push({cur.a, B, cur.ops + "fill B\n"});
            }
            if (cur.a > 0 && !visited[{0, cur.b}]) {
                visited[{0, cur.b}] = true;
                q.push({0, cur.b, cur.ops + "empty A\n"});
            }
            if (cur.b > 0 && !visited[{cur.a, 0}]) {
                visited[{cur.a, 0}] = true;
                q.push({cur.a, 0, cur.ops + "empty B\n"});
            }
            // pour A -> B
            if (cur.a > 0 && cur.b < B) {
                int pour = min(cur.a, B - cur.b);
                int na = cur.a - pour, nb = cur.b + pour;
                if (!visited[{na, nb}]) {
                    visited[{na, nb}] = true;
                    q.push({na, nb, cur.ops + "pour A B\n"});
                }
            }
            // pour B -> A
            if (cur.b > 0 && cur.a < A) {
                int pour = min(cur.b, A - cur.a);
                int na = cur.a + pour, nb = cur.b - pour;
                if (!visited[{na, nb}]) {
                    visited[{na, nb}] = true;
                    q.push({na, nb, cur.ops + "pour B A\n"});
                }
            }
        }
    }
    return 0;
}
