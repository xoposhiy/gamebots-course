// https://www.codingame.com/ide/puzzle/search-race
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("omit-frame-pointer")
#pragma GCC optimize("unroll-loops")
#include "math.h"
#include <iostream>
#include <vector>

// TODO: you shell experiment with different DEPTH values
#define DEPTH 1

using namespace std;

struct Point {
    int x, y;
};

inline int rnd(int b) {
    return rand() % b;
}

inline int rnd(int a, int b) {
    return a + rnd(b - a + 1);
}

/// Normalize angle to be in the range -180..180
int norm_angle(int a) {
    a = a % 360;
    if (a < -180) return a + 360;
    if (a > 180) return a - 360;
    return a;
}

struct Move {
    int x, y, thrust;

    Move(int x = 0, int y = 0, int thrust = 0)
        : x(x), y(y), thrust(thrust) {}

    void print() const {
        cout << x << " " << y << " " << thrust << endl;
    }
};

struct State {
    const vector<Point>& checkpoints; // immutable
    int checkpoint_index;
    double x, y, vx, vy, angle;

    State(const vector<Point>& checkpoints, int checkpoint_index, int x, int y, int vx, int vy, int angle)
        : checkpoints(checkpoints), checkpoint_index(checkpoint_index), x(x), y(y), vx(vx), vy(vy), angle(angle) {}

    State(const State& other)
        : checkpoints(other.checkpoints), checkpoint_index(other.checkpoint_index), x(other.x), y(other.y), vx(other.vx), vy(other.vy), angle(other.angle) {}

    void print() const {
        cerr << "State(" 
            << "checkpoint_index=" << checkpoint_index 
            << ", x=" << x << ", y=" << y
            << ", vx=" << vx << ", vy=" << vy 
            << ", angle=" << angle << ")" << endl;
    }

    Point get_checkpoint(int index = 0) const {
        return checkpoints[(checkpoint_index + index) % checkpoints.size()];
    }

    void simulate(const Move& move) {
        double desired_angle = 180.0 * atan2(move.y - y, move.x - x) / M_PI;
        int da = norm_angle(desired_angle - angle);
        da = max(-18, min(18, da));
        angle = angle + da;
        vx += move.thrust * cos(angle * M_PI / 180.0);
        vy += move.thrust * sin(angle * M_PI / 180.0);
        x = static_cast<int>(x + vx);
        y = static_cast<int>(y + vy);
        vx = static_cast<int>(0.85 * vx);
        vy = static_cast<int>(0.85 * vy);
        angle = static_cast<int>(round(angle)) % 360;
        Point cp = get_checkpoint();
        int dx = x - cp.x, dy = y - cp.y;
        if (dx * dx + dy * dy < 590 * 590) {
            checkpoint_index++;
        }
    }
};

double estimate(const State& state){
    // TODO: implement your own estimation function
    // Calculates the score of the state.
    // The higher the checkpoint_index, the better.
    // The closer to the next checkpoint, the better.
    // ... [your ideas here] ...
    return 0;
}

inline Move create_random_move(){
    // TODO: Create random Move instance:
    return Move(5000, 5000, 200);
} 

/// Random search with a time limit
void random_search(State& state, Move best_moves[], clock_t end_time) {
    double best_score = -std::numeric_limits<double>::infinity();
    int simulations_count = 0;
    while (clock()  < end_time) {
        // TODO: Finish an implementation of the Monte Carlo algorithm a.k.a random search
        // While still have time, create a new random sequence of moves (use create_random_move).
        // Simulate this sequence of moves (use state.simulate(move)).
        // Estimate the final state after simulation and store the best sequence. (use estimate(state))
        // Store the best move sequence in best_moves[]

        simulations_count++;
    }
    cerr << best_score << " sims: " << simulations_count << endl;
}

vector<Point> read_checkpoints() {
    int n;
    cin >> n;
    vector<Point> checkpoints(n);
    for (int i = 0; i < n; ++i)
        cin >> checkpoints[i].x >> checkpoints[i].y;
    return checkpoints;
}

int main() {
    vector<Point> checkpoints = read_checkpoints();

    Move best_moves[DEPTH];
    while (true) {
        int checkpoint_index, x, y, vx, vy, angle;
        cin >> checkpoint_index >> x >> y >> vx >> vy >> angle; // input current state

        /// Actual time per move is 50ms, but to avoid random timeouts we cut it in half
        clock_t end_time = clock() + 0.025 * CLOCKS_PER_SEC;
        State state(checkpoints, checkpoint_index, x, y, vx, vy, angle);
        random_search(state, best_moves, end_time);

        best_moves[0].print(); // output our next move!
    }
    return 0;
}
