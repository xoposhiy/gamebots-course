#include <iostream>
#include <cmath>

using namespace std;

struct Point {
    int x, y;
};

// Function to normalize angle to the range -180 to 180
int norm_angle(int a) {
    a = a % 360;
    if (a > 180.0) return a - 360;
    if (a < -180) return a + 360;
    return a;
}

// AI function to decide the next move
void ai(const Point checkpoints[], int cp_index, int x, int y, int vx, int vy, int heading) {
    int cx = checkpoints[cp_index].x;
    int cy = checkpoints[cp_index].y;
    int dx = cx - x;
    int dy = cy - y;
    float cp_heading = atan2(dy, dx) * 180 / M_PI;
    float da = norm_angle(cp_heading - heading);

    // TODO: Finishe the code!
    // If the car is facing the next checkpoint, then go at full thrust.
    // else, turn towards the checkpoint.
    // But if the car speed is high enough to get to the next checkpoint without thrust,
    // then set thrust to zero and use this time wisely.

    cout << cx << " " << cy << " 100" << endl;
}

// Function to read checkpoints
void read_checkpoints(Point checkpoints[], int n) {
    for (int i = 0; i < n; ++i) {
        cin >> checkpoints[i].x >> checkpoints[i].y;
    }
}

int main() {
    int n;
    cin >> n;
    Point checkpoints[n];
    read_checkpoints(checkpoints, n);
    
    while (true) {
        int checkpoint_index, x, y, vx, vy, heading;
        cin >> checkpoint_index >> x >> y >> vx >> vy >> heading;
        ai(checkpoints, checkpoint_index, x, y, vx, vy, heading);
    }

    return 0;
}
