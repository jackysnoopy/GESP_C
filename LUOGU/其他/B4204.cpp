#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, A, B;
    cin >> N >> M >> A >> B;
    // Simulate: M robots, N vegetables.
    // Each vegetable needs wash (A min) then cook (B min).
    // Robots pick up available tasks greedily.
    // Event-driven simulation with priority queue of robot available times.
    // But n,m <= 2000, so simple simulation is fine.
    // Track when each robot becomes free. Use a priority queue (min-heap).
    // Actually, just use an array of robot free times.
    long long robotFree[2001];
    for (int i = 0; i < M; i++) robotFree[i] = 0;
    // For each vegetable: find earliest available robot for washing, then for cooking.
    // Actually, the problem says: when a robot is free, it picks the next available task.
    // Wash first, then cook.
    // This is a simulation problem.
    // We need to track: for each vegetable, when was it washed (and by which robot).
    // And when can it start cooking.
    // 
    // Simplify: use two priority queues.
    // wash_q: when robots become available for washing.
    // cook_q: when robots become available for cooking (and vegetables are washed).
    // 
    // Actually, the problem is more nuanced. The robots are shared between washing and cooking.
    // A robot first washes, then if it's free and there's a vegetable ready to cook, it cooks.
    // Otherwise, it washes the next vegetable.
    
    // Let me simulate with events.
    // Each robot has a state: free at time t.
    // Events: robot becomes free at time t.
    // When robot becomes free:
    //   If there's a vegetable waiting to cook: cook it (robot free at t+B).
    //   Else if there's a vegetable waiting to wash: wash it (robot free at t+A).
    //   Else: robot is idle.
    
    // We process events in time order.
    // Vegetables are processed in order (1 to N).
    // Wash queue: vegetables waiting to be washed.
    // Cook queue: vegetables waiting to be cooked.
    
    int washQueue = 0; // number of vegetables waiting to be washed
    int cookQueue = 0; // number of vegetables waiting to be cooked
    long long washDone[2001]; // when each vegetable finishes washing
    
    // Use a min-heap for robot free times
    // Simple approach: array of free times, always pick the earliest free robot
    
    long long washEnd[2001]; // when each vegetable finishes washing
    int nextWash = 0; // next vegetable to start washing
    int nextCook = 0; // next vegetable ready to cook (finished washing)
    
    // Process: assign washing tasks to robots
    // Then assign cooking tasks to robots
    
    // Actually, let me think about this differently.
    // The key insight: washing and cooking happen in two phases.
    // But robots can interleave: a robot washes, then cooks, then washes, etc.
    //
    // For the greedy strategy described:
    // When a robot is free: if there are vegetables waiting to cook, cook one.
    // Else if there are vegetables waiting to wash, wash one.
    // 
    // This is equivalent to: all washing happens as early as possible,
    // and cooking happens as soon as a washed vegetable and a free robot are available.
    
    // Simulation:
    // Maintain a min-heap of robot free times.
    // Maintain a queue of washed vegetables (ready to cook).
    // Maintain a counter for vegetables to wash.
    
    // For N, M, A, B up to 2000, we can simulate step by step.
    
    // Approach: event-driven simulation.
    // Events: (time, robot_id, task_type).
    // task_type: 0 = finished washing, 1 = finished cooking.
    
    // Simpler approach: just track when each robot is free.
    long long rfree[2001];
    for (int i = 0; i < M; i++) rfree[i] = 0;
    
    int vegWashed = 0; // how many vegetables have been washed
    int vegCooked = 0; // how many vegetables have been cooked
    long long washFinish[2001]; // when vegetable i finishes washing
    
    // Phase 1: assign washing tasks
    // For each vegetable, find the earliest free robot, assign washing.
    for (int v = 0; v < N; v++) {
        // Find earliest free robot
        int best = 0;
        for (int r = 1; r < M; r++) {
            if (rfree[r] < rfree[best]) best = r;
        }
        rfree[best] += A;
        washFinish[v] = rfree[best];
    }
    
    // Phase 2: assign cooking tasks
    // For each vegetable (in order of wash finish time), find earliest free robot.
    // But robots might still be washing in phase 1!
    // The issue: phase 1 and phase 2 overlap in time.
    
    // Better simulation: process events in time order.
    // Use a priority queue for robot free times.
    // Track: vegetables waiting to wash, vegetables waiting to cook.
    
    // Let me use a different approach.
    // The greedy: when a robot becomes free, it picks the highest priority available task.
    // Priority: cooking > washing (because we want to finish cooking ASAP).
    
    // But the problem says: wash first if available, then cook.
    // "如果有青菜还没被清洗，就让这个机器人清洗这根青菜，否则如果有青菜还没被水煮..."
    // So WASHING has higher priority than cooking!
    
    // This means: robots always wash first until all vegetables are washed,
    // then they start cooking.
    // Wait, that can't be right. If a vegetable is already washed and waiting to cook,
    // and a robot is free, it should cook it (since there are no more vegetables to wash).
    // But if there are still vegetables to wash, it washes first.
    
    // So the order is: always wash if possible, else cook.
    // This means: all washing happens first, then all cooking.
    
    // For washing N vegetables with M robots:
    // Each robot washes ceil(N/M) vegetables (approximately).
    // The wash phase ends at time: max over robots of (number of vegetables washed by that robot) * A.
    // Optimal: distribute evenly. Robot i washes floor(N/M) or ceil(N/M) vegetables.
    // The last vegetable finishes washing at: ceil(N/M) * A.
    
    // For cooking N vegetables with M robots:
    // Same as washing but with time B per vegetable.
    // But cooking can only start AFTER the vegetable is washed.
    // And the cooking phase starts when the first vegetable is washed.
    
    // Actually, the greedy says: when a robot is free, if there are vegetables to wash, wash.
    // This means robots don't start cooking until ALL vegetables are washed.
    // Because there are always vegetables to wash (until all are washed).
    
    // Wait, that's only true if N >= M. If N < M, some robots are idle during washing.
    // And those idle robots can start cooking the already-washed vegetables.
    
    // Let me re-read: "每当一个机器人空下来：如果有青菜还没被清洗，就让这个机器人清洗这根青菜"
    // So if ANY vegetable hasn't been washed, the robot washes. Even if there are
    // vegetables ready to cook.
    
    // This means: all washing happens before any cooking.
    // Except: if a robot finishes washing and there are no more vegetables to wash,
    // it starts cooking.
    
    // So the washing phase: M robots wash N vegetables.
    // Wash phase end time: depends on distribution.
    // With M robots and N vegetables: robot i washes roughly N/M vegetables.
    // The last wash finishes at: the time when the last robot finishes its last wash.
    
    // Cooking phase: starts after wash phase (or earlier if some robots are idle).
    // If N <= M: all vegetables can be washed simultaneously. Wash ends at A.
    //   Then cooking starts. M robots cook N vegetables. Cook ends at A + B (for last one).
    //   Wait, not exactly. If N=1, M=2: robot 1 washes (ends at A), robot 2 is idle.
    //   Robot 2 starts cooking at time A (when the vegetable is washed). Ends at A+B.
    //   But robot 1 also becomes free at A. If there's nothing to wash, it cooks.
    //   But there's only 1 vegetable, so robot 1 is idle.
    
    // Let me just simulate properly.
    
    // Reset
    for (int i = 0; i < M; i++) rfree[i] = 0;
    
    // Simulate the greedy process
    int vegToWash = N;
    int vegToCook = 0;
    // Queue of washed vegetables (ready to cook)
    // We don't need to track individual vegetables, just counts.
    
    // Event-driven: process robot free events
    // At each event, assign a task to the robot.
    
    // Since M, N <= 2000, we can simulate step by step.
    // Use a priority queue (min-heap) for robot free times.
    
    // Actually, let me use a simple array and find the min each time.
    // Total events: N (wash) + N (cook) = 2N <= 4000.
    // Each event: find min robot free time. O(M).
    // Total: O(N*M) = 4e6. Fine.
    
    for (int i = 0; i < M; i++) rfree[i] = 0;
    
    int washIdx = 0; // next vegetable to wash (0-indexed)
    int washDoneCount = 0;
    int cookIdx = 0; // next vegetable to cook
    long long washEndTime[2001]; // when each vegetable finishes washing
    
    // Simulate events
    while (cookIdx < N) {
        // Find earliest free robot
        int best = 0;
        for (int r = 1; r < M; r++) {
            if (rfree[r] < rfree[best]) best = r;
        }
        long long t = rfree[best];
        
        if (washIdx < N) {
            // There are vegetables to wash. Wash one.
            rfree[best] = t + A;
            washEndTime[washIdx] = t + A;
            washIdx++;
        } else if (cookIdx < washIdx) {
            // All washed, start cooking
            // But can only cook if the vegetable is already washed
            // cookIdx < washIdx means there are washed vegetables waiting
            // But we need to check: is washEndTime[cookIdx] <= t?
            // Since we always wash before cook, and we process in time order,
            // washEndTime[cookIdx] should be <= t.
            rfree[best] = t + B;
            cookIdx++;
        } else {
            // This shouldn't happen
            break;
        }
    }
    
    // The answer is the maximum robot free time
    long long ans = 0;
    for (int r = 0; r < M; r++) {
        if (rfree[r] > ans) ans = rfree[r];
    }
    cout << ans << "\n";
    return 0;
}
