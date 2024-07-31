# Typical problems in simple task

Debug method: print debug message after the command:

    cout << cx << " " << cy << " " << thrust << " " << dubug_message << endl;

use debug message to output delta_angle, distance to checkpoint, ... 


# Typical problems in monte carlo task

**Problem:** Car is moving randomly.

**Possible reason:** The simulation is made not on the copy of state, but on initia state.

**Problem:** Car stops just before the checkpoint.

**Possible reason:** Too small weight of checkpoint_index in estimation function.
If squared distance (w/o sqrt) is used, the weight should be squared.

**Problem:** Noisy car movement

**Possible reason:** Too big value of DEPTH

**Problem:** Car circles around the checkpoint

**Possible reason:** Too small value of DEPTH

**Problem:** Failed tests after submission

**Possible reason:** Random timelimits. Decrease time limit to 25ms

    clock_t end_time = clock() + 0.025 * CLOCKS_PER_SEC;

