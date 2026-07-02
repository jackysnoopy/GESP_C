#include <iostream>
#include <vector>
using namespace std;

int n = 5;
int grid[5][5];
int top[5] = {2, 2, 1, 3, 3};
int bottom[5] = {1, 4, 2, 2, 3};
int left_[5] = {2, 2, 3, 2, 1};
int right_[5] = {3, 3, 1, 2, 4};
bool used_row[5][6];
bool used_col[5][6];

bool checkVisible(int arr[], int constraint) {
    int count = 0, maxHeight = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxHeight) {
            maxHeight = arr[i];
            count++;
        }
    }
    return count == constraint;
}

bool solve(int row, int col) {
    if (row == n) return true;
    int nextRow = (col == n - 1) ? row + 1 : row;
    int nextCol = (col == n - 1) ? 0 : col + 1;
    for (int val = 1; val <= n; val++) {
        if (used_row[row][val] || used_col[col][val]) continue;
        grid[row][col] = val;
        used_row[row][val] = true;
        used_col[col][val] = true;
        bool ok = true;
        if (col == n - 1) {
            int arr[5];
            for (int i = 0; i < n; i++) arr[i] = grid[row][i];
            if (!checkVisible(arr, left_[row])) ok = false;
            if (ok) {
                for (int i = 0; i < n; i++) arr[i] = grid[row][n - 1 - i];
                if (!checkVisible(arr, right_[row])) ok = false;
            }
        }
        if (ok && row == n - 1) {
            int arr[5];
            for (int i = 0; i < n; i++) arr[i] = grid[i][col];
            if (!checkVisible(arr, top[col])) ok = false;
            if (ok) {
                for (int i = 0; i < n; i++) arr[i] = grid[n - 1 - i][col];
                if (!checkVisible(arr, bottom[col])) ok = false;
            }
        }
        if (ok) {
            if (solve(nextRow, nextCol)) return true;
        }
        grid[row][col] = 0;
        used_row[row][val] = false;
        used_col[col][val] = false;
    }
    return false;
}

int main() {
    solve(0, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cout << grid[i][j];
    cout << endl;
    return 0;
}
