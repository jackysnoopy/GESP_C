#include <iostream>
#include <deque>
#include <vector>
#include <cstdio>
using namespace std;

struct Pile {
    deque<int> cards;
};

int main() {
    vector<int> deck;
    int card;
    while (cin >> card && card != 0) {
        deck.push_back(card);
    }
    
    int start = 0;
    int n = deck.size();
    
    Pile piles[7];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 5; j++) {
            piles[i].cards.push_back(deck[start++]);
        }
    }
    
    vector<int> remaining;
    for (; start < n; start++) {
        remaining.push_back(deck[start]);
    }
    int remIdx = 0;
    
    bool gameOver = false;
    int moves = 0;
    
    while (!gameOver) {
        gameOver = true;
        moves++;
        
        for (int i = 0; i < 7; i++) {
            if (piles[i].cards.empty()) continue;
            int top = piles[i].cards.front();
            
            bool moved = false;
            
            if (top == 10 || top == 20 || top == 30) {
                piles[i].cards.pop_front();
                moved = true;
            } else if (i >= 1 && !piles[i-1].cards.empty() && 
                       top + piles[i-1].cards.front() == 30) {
                piles[i-1].cards.pop_front();
                piles[i].cards.pop_front();
                moved = true;
            } else if (i >= 2 && !piles[i-2].cards.empty() && 
                       top + piles[i-2].cards.front() == 30) {
                piles[i-2].cards.pop_front();
                piles[i].cards.pop_front();
                moved = true;
            } else if (i <= 5 && !piles[i+1].cards.empty() && 
                       top + piles[i+1].cards.front() == 30) {
                piles[i+1].cards.pop_front();
                piles[i].cards.pop_front();
                moved = true;
            } else if (i <= 4 && !piles[i+2].cards.empty() && 
                       top + piles[i+2].cards.front() == 30) {
                piles[i+2].cards.pop_front();
                piles[i].cards.pop_front();
                moved = true;
            }
            
            if (moved) {
                gameOver = false;
                if (piles[i].cards.empty() && remIdx < (int)remaining.size()) {
                    piles[i].cards.push_back(remaining[remIdx++]);
                }
                for (int j = 0; j < 7; j++) {
                    if (piles[j].cards.empty() && remIdx < (int)remaining.size()) {
                        piles[j].cards.push_back(remaining[remIdx++]);
                    }
                }
                break;
            }
        }
    }
    
    bool allEmpty = true;
    for (int i = 0; i < 7; i++) {
        if (!piles[i].cards.empty()) {
            allEmpty = false;
            break;
        }
    }
    
    if (allEmpty) {
        printf("Win after %d moves\n", moves);
    } else {
        printf("Loss after %d moves\n", moves);
        printf("Cards remaining:");
        for (int i = 0; i < 7; i++) {
            for (int c : piles[i].cards) {
                printf(" %d", c);
            }
        }
        printf("\n");
    }
    
    return 0;
}
