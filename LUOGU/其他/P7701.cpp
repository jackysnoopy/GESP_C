#include <iostream>
#include <vector>
using namespace std;

// [CCC 2014] 提前交卷
// Complex simulation: n rows, 6 seats (A-F), m students leave early.
// Each student's dissatisfaction = A*x + B*y where x = people passed, y = people in safe room.
// Greedy: send students to the nearest safe room (front or back) that minimizes cost.
// The key insight is the ordering of who leaves when.
//
// For each student, going to front safe room: pass all people in front in the aisle.
// Going to back: pass all people behind in the aisle.
// y increases each time someone enters the safe room.
//
// With n rows, 6 seats per row (A,B,C | D,E,F), aisle between C and D.
// When leaving seat (r, c): go to aisle (pass same-row people between seat and aisle),
// then go along aisle to safe room (pass people in aisle going to same safe room).
//
// Seats A,B,C are on the left, D,E,F on the right.
// Left seats (A,B,C) going to front: pass through row (other left-seat people in this row)
//   then go forward through aisle.
// Right seats (D,E,F) going to back: pass through row then go backward.
//
// Actually, students choose which safe room to go to. We need to find optimal assignments
// to minimize total dissatisfaction.
//
// For simplicity: each student can go to front or back. 
// Going to front from seat (r,c):
//   x = (people in same row between c and aisle) + (people in rows 1..r-1 at the aisle)
// Going to back from seat (r,c):
//   x = (people in same row between c and aisle) + (people in rows r+1..n at the aisle)
//
// This is complex. Let me implement a greedy: sort students by some criterion, assign optimally.
//
// Actually the problem says they leave sequentially (in the order given).
// For each student, they choose front or back to minimize their own cost.
// But the y component depends on previous students' choices.
//
// This requires careful simulation. Let me implement it.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, A, B;
    cin >> n >> m >> A >> B;
    
    // seat layout: row r, seat c (0=A,1=B,2=C,3=D,4=E,5=F)
    // Aisle between c=2 and c=3
    // People between seat and aisle:
    //   Left (A,B,C): aisle_dist = 2-c (A:2, B:1, C:0)
    //   Right (D,E,F): aisle_dist = c-3 (D:0, E:1, F:2)
    
    vector<int> r(m), c(m);
    vector<string> seat(m);
    for (int i = 0; i < m; i++) {
        cin >> r[i] >> seat[i];
        c[i] = seat[i][0] - 'A';
    }
    
    // Track occupied seats
    vector<vector<bool>> occupied(n + 1, vector<bool>(6, true));
    int frontCount = 0, backCount = 0;
    long long totalDissatisfaction = 0;
    
    for (int i = 0; i < m; i++) {
        int ri = r[i], ci = c[i];
        occupied[ri][ci] = false;
        
        bool isLeft = (ci <= 2);
        int aisleDist = isLeft ? (2 - ci) : (ci - 3);
        
        // Count people between this seat and the aisle (same row, already left)
        int sameRow = 0;
        if (isLeft) {
            for (int j = ci + 1; j <= 2; j++) {
                if (occupied[ri][j]) sameRow++;
            }
        } else {
            for (int j = ci - 1; j >= 3; j--) {
                if (occupied[ri][j]) sameRow++;
            }
        }
        
        // Count people in aisle going to front (rows 1..ri-1, seats C and D that have left)
        int frontPass = 0, backPass = 0;
        // Actually the "people passed" in the aisle are people who are in the aisle
        // (i.e., in the same column as the aisle) in rows we pass through.
        // But the aisle doesn't have seats - it's between C and D.
        // People "in the aisle" means people in seats C or D who have left?
        // No, I think x counts all people you physically walk past.
        // You walk past same-row people to reach the aisle, then walk along the aisle.
        // In the aisle, you walk past people sitting in C (going left->front) or D (going right->back)?
        // 
        // Actually I think x = number of people whose seats you walk past.
        // When going to front from left seat: walk past people in seats to your right up to aisle (C),
        //   then walk forward along aisle past people in C seats in rows ahead.
        // When going to front from right seat: walk past people in seats to your left up to aisle (D),
        //   then walk forward along aisle past people in D seats in rows ahead.
        // Hmm, this is getting complicated.
        
        // Let me just compute both costs and choose the minimum
        // Front: x = sameRow + people in rows 1..ri-1 who have seats C (for left) or D (for right)
        // Back: x = sameRow + people in rows ri+1..n who have seats C (for left) or D (for right)
        // But "people in the aisle" = people sitting at the aisle seat (C or D) that are still occupied?
        // No, they need to have left too for you to pass them... 
        // Actually you pass by seats, not by people. Empty seats don't count.
        
        // I think x counts people you walk past (occupied seats you pass by).
        // Let me just count for front and back:
        
        int frontX = sameRow;
        int backX = sameRow;
        
        // Forward along aisle: pass rows 1 to ri-1
        for (int row = 1; row < ri; row++) {
            if (isLeft) {
                // Pass people in seat C (index 2) of this row
                if (occupied[row][2]) frontX++;
            } else {
                if (occupied[row][3]) frontX++;
            }
        }
        // Backward along aisle: pass rows ri+1 to n
        for (int row = ri + 1; row <= n; row++) {
            if (isLeft) {
                if (occupied[row][2]) backX++;
            } else {
                if (occupied[row][3]) backX++;
            }
        }
        
        long long frontCost = (long long)A * frontX + (long long)B * frontCount;
        long long backCost = (long long)A * backX + (long long)B * backCount;
        
        if (frontCost <= backCost) {
            totalDissatisfaction += frontCost;
            frontCount++;
        } else {
            totalDissatisfaction += backCost;
            backCount++;
        }
    }
    
    cout << totalDissatisfaction << "\n";
    return 0;
}
