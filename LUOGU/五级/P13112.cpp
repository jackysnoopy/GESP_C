#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 判断 a 是否能赢 b
bool beats(char a, char b) {
    return (a == 'R' && b == 'S') || (a == 'P' && b == 'R') || (a == 'S' && b == 'P');
}

// 检查程序 p 是否能赢对手 opp
bool canBeat(const string& p, const string& opp) {
    int pi = 0, oi = 0;
    int moves = 0;
    int maxMoves = 1000; // 足够大的次数
    
    while (moves < maxMoves) {
        if (beats(p[pi], opp[oi])) {
            return true; // 我们赢了
        }
        if (beats(opp[oi], p[pi])) {
            return false; // 对手赢了
        }
        // 平局，继续下一轮
        pi = (pi + 1) % p.size();
        oi = (oi + 1) % opp.size();
        moves++;
    }
    return false; // 如果一直平局，我们算输
}

int main() {
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int A;
        cin >> A;
        
        vector<string> opponents(A);
        for (int i = 0; i < A; i++) {
            cin >> opponents[i];
        }
        
        // 简单策略：尝试所有长度为 1 的程序
        string result = "IMPOSSIBLE";
        vector<char> chars = {'R', 'P', 'S'};
        
        for (char c : chars) {
            string program(1, c);
            bool ok = true;
            for (const string& opp : opponents) {
                if (!canBeat(program, opp)) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                result = program;
                break;
            }
        }
        
        // 如果长度 1 不行，尝试长度 2
        if (result == "IMPOSSIBLE") {
            for (char c1 : chars) {
                for (char c2 : chars) {
                    string program = "";
                    program += c1;
                    program += c2;
                    bool ok = true;
                    for (const string& opp : opponents) {
                        if (!canBeat(program, opp)) {
                            ok = false;
                            break;
                        }
                    }
                    if (ok) {
                        result = program;
                        break;
                    }
                }
                if (result != "IMPOSSIBLE") break;
            }
        }
        
        // 如果长度 2 不行，尝试长度 3
        if (result == "IMPOSSIBLE") {
            for (char c1 : chars) {
                for (char c2 : chars) {
                    for (char c3 : chars) {
                        string program = "";
                        program += c1;
                        program += c2;
                        program += c3;
                        bool ok = true;
                        for (const string& opp : opponents) {
                            if (!canBeat(program, opp)) {
                                ok = false;
                                break;
                            }
                        }
                        if (ok) {
                            result = program;
                            break;
                        }
                    }
                    if (result != "IMPOSSIBLE") break;
                }
                if (result != "IMPOSSIBLE") break;
            }
        }
        
        cout << "Case #" << t << ": " << result << endl;
    }
    
    return 0;
}
