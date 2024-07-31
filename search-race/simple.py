# https://www.codingame.com/ide/puzzle/search-race

import math

def ai(checkpoints, cp_index, x, y, vx, vy, heading):
    """
    If the car is facing the next checkpoint, then go at full thrust.
    else, turn towards the checkpoint.

    TODO: 
    If the car speed is high enough to get to the next checkpoint without thrust,
    then set thrust to zero and chill out.
    """
    cx, cy = checkpoints[cp_index]
    dx = cx - x
    dy = cy - y
    cp_heading = math.atan2(dy, dx) * 180 / math.pi
    da = norm_angle(cp_heading - heading)
    if abs(da) < 15:
        return f"{cx} {cy} 200 GO-GO-GO!"
    return f"{cx} {cy} 0 where is my checkpoint?"


def norm_angle(a: float) -> float:
    """
    Normalize angle to -180..180 range.
    """
    a = a % 360  # 0..360
    if a > 180:
        a -= 360  # -180..180
    return a


def read_checkpoints():
    n = int(input())  # number of checkpoints
    checkpoints = []
    for i in range(n):
        x, y = [int(j) for j in input().split()]
        checkpoints.append((x, y))
    return checkpoints


def main():
    checkpoints = read_checkpoints()
    while True:
        checkpoint_index, x, y, vx, vy, heading = [int(i) for i in input().split()]
        move = ai(checkpoints, checkpoint_index, x, y, vx, vy, heading)
        print(move)

if __name__ == '__main__':
    main()
