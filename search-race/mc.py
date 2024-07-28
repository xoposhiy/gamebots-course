import random
import sys
import math
import time


def norm_angle(a):
    a = a % 360  # a in 0..360
    if a > 180:
        a -= 360  # a in -180..180
    return a


class Move:
    def __init__(self, x, y, thrust, message=""):
        self.x, self.y, self.thrust, self.message = x, y, thrust, message

    def __str__(self):
        return f'{self.x} {self.y} {self.thrust} {self.message}'


class State:
    def __init__(self, checkpoints, checkpoint_index, x, y, vx, vy, angle):
        self.checkpoints = checkpoints
        self.checkpoint_index = checkpoint_index
        self.x = x
        self.y = y
        self.vx = vx
        self.vy = vy
        self.angle = angle


    def __str__(self):
        return f'State(checkpoints, {self.checkpoint_index}, {self.x}, {self.y}, {self.vx}, {self.vy}, {self.angle})'


    def copy(self):
        return State(self.checkpoints, self.checkpoint_index, self.x, self.y, self.vx, self.vy, self.angle)


    def cur_checkpoint(self):
        return self.checkpoints[self.checkpoint_index % len(self.checkpoints)]


    def simulate(self, move: Move):
        desired_angle = 180 * math.atan2(move.y - self.y, move.x - self.x) / math.pi
        da = norm_angle(desired_angle - self.angle)
        da = max(-18, min(18, da))
        self.angle = self.angle + da
        self.vx += move.thrust * math.cos(self.angle * math.pi / 180)
        self.vy += move.thrust * math.sin(self.angle * math.pi / 180)
        self.x = int(self.x + self.vx)
        self.y = int(self.y + self.vy)
        self.vx = int(0.85 * self.vx)
        self.vy = int(0.85 * self.vy)
        self.angle = round(self.angle) % 360

        # simplified checkpoint-collision check
        xc, yc = self.cur_checkpoint()
        dx, dy = self.x - xc, self.y - yc
        if dx * dx + dy * dy < 590 * 590:
            self.checkpoint_index += 1


def estimate(state):
    """
    Calculates the score of the state.
    The higher the checkpoint_index, the better.
    The closer to the next checkpoint, the better.
    ... [your ideas here] ...
    """
    # TODO 1
    pass


def create_random_moves(depth):
    """
    Returns an array of depth random Move objects.
    ... (or not so random) ...
    """
    # TODO 2
    pass


def random_search(state, depth):
    """
    Implementation of the Monte Carlo algorithm a.k.a random search
    
    While still have time, create a new random sequence of moves (use create_random_moves).
    Simulate this sequence of moves (use state.simulate(move)).
    Evaluate the final state after simulation and store the best sequence.

    When time (50ms) runs out, returns the best sequence of moves.
    
    To track time, use the time.time() function that returns the current time in seconds.
    """
    best_moves = []
    best_score = -math.inf
    simulations_count = 0  # number of random solutions that were considered
    
    # TODO 3: random search implementation here

    # debug output: best found score; number of estimated sequences; best sequence of moves
    print(best_score, simulations_count, list(map(str, best_moves)), file=sys.stderr)
    return best_moves


def read_checkpoints():
    n = int(input())
    checkpoints = []
    for i in range(n):
        x, y = [int(j) for j in input().split()]
        checkpoints.append((x, y))
    return checkpoints


def main():
    checkpoints = read_checkpoints()
    print(f'checkpoints={checkpoints}', file=sys.stderr)
    best_moves = None
    while True:
        state = State(checkpoints, *list(map(int, input().split())))
        print(state, file=sys.stderr)
        
        # TODO 4: experiment with different depths
        best_moves = random_search(state, depth=1)
        best_move = best_moves[0]
        print(best_move)

if __name__ == '__main__':
    main()