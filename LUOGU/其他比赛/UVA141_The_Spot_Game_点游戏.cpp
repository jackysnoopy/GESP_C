// UVA141 - The Spot Game (点游戏)
// 两人在5x5网格上操作，判断谁获胜
#include <iostream>
#include <vector>

const int N = 5;

// 检查棋盘是否旋转对称
bool isRotationalSymmetry(bool board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] != board[N - 1 - j][N - 1 - i]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int n;
    
    while (std::cin >> n && n != 0) {
        bool board[N][N] = {false};
        int winner = 0;
        int moveNum = 0;
        
        for (int i = 1; i <= n; i++) {
            int x, y;
            char op;
            
            std::cin >> x >> y >> op;
            x--; // 转换为0-indexed
            y--;
            
            if (winner != 0) continue; // 游戏已结束，继续读取输入
            
            // 执行操作
            if (op == '+') {
                board[x][y] = true;
            } else if (op == '-') {
                board[x][y] = false;
            } else if (op == '@') {
                board[x][y] = true;
                board[N - 1 - y][N - 1 - x] = true;
            }
            
            // 检查旋转对称
            if (isRotationalSymmetry(board)) {
                winner = (i % 2 == 1) ? 2 : 1; // 对方获胜
                moveNum = i;
            }
        }
        
        // 输出结果
        if (winner == 1) {
            std::cout << "Player 1 wins after move " << moveNum << std::endl;
        } else if (winner == 2) {
            std::cout << "Player 2 wins after move " << moveNum << std::endl;
        } else {
            std::cout << "Draw" << std::endl;
        }
    }
    
    return 0;
}
