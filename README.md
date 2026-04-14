# Philosophers

*This project has been created as part of the 42 curriculum by lleineck.*

## Description

**Philosophers** is a multithreaded simulation project based on the classic **Dining Philosophers Problem**, a well-known synchronization challenge in computer science.

### Project Goal

The project teaches the fundamentals of:
- **Threading**: Creating and managing multiple threads in a C program
- **Mutex synchronization**: Using mutexes to prevent race conditions and protect shared resources
- **Deadlock prevention**: Implementing strategies to avoid circular wait scenarios

### Overview

In this simulation:
- **N philosophers** sit around a **circular table** with a bowl of spaghetti in the middle
- There are exactly **N forks** (one between each pair of philosophers)
- Each philosopher cycles through three states: **eating**, **sleeping**, and **thinking**
- A philosopher must acquire **both adjacent forks** before eating
- **The simulation ends** when:
  - A philosopher dies of starvation (hasn't eaten within `time_to_die` milliseconds), OR
  - All philosophers have eaten the required number of times (if specified)

### Key Mechanics

- **Each philosopher is a separate thread** that manages its own lifecycle
- **Mutexes protect each fork** to ensure mutual exclusion
- **A monitor thread** checks for philosopher deaths and meal completion
- **No philosopher can starve** if the timing allows proper synchronization

---

## Instructions

### Compilation

To compile the mandatory part:

```bash
cd philosophers
make
```

This generates the `philo` executable.

To compile with verbose flags for debugging:

```bash
make clean
make all
```

### Cleaning

Remove compiled objects:
```bash
make clean
```

Remove all compiled files including the executable:
```bash
make fclean
```

Recompile from scratch:
```bash
make re
```

### Execution

Run the simulation with these arguments:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
```

**Arguments:**
- `number_of_philosophers`: Number of philosophers (and forks)
- `time_to_die` (ms): Time before a philosopher starves if they don't eat
- `time_to_eat` (ms): Duration of eating state
- `time_to_sleep` (ms): Duration of sleeping state
- `number_of_meals` (optional): If all philosophers eat this many times, simulation ends

### Examples

**Two philosophers with 400ms death timer:**
```bash
./philo 2 400 200 200
```

**Five philosophers, each must eat 10 times:**
```bash
./philo 5 800 200 200 10
```

**31 philosophers, stress test:**
```bash
./philo 31 599 200 200 10
```

### Output Format

Each state change is logged in real-time:

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 2 has taken a fork
200 2 is eating
...
400 1 died
```

**Format**: `<timestamp_ms> <philosopher_id> <state>`

---

## Technical Details

### Architecture

#### Core Components

1. **philosophers.c**: Thread initialization and philosopher behavior loop
2. **eaten.c**: Fork acquisition logic with deadlock prevention
3. **hecate.c**: Monitor thread that checks for deaths and meal completion
4. **mutex.c**: Mutex initialization and cleanup
5. **utils.c**: Utility functions (timestamps, state printing, sleep)
6. **parsing.c**: Command-line argument validation

#### Data Structures

```c
typedef struct s_philo
{
    int             id;              // Philosopher identifier (1 to N)
    long            last_meal;       // Timestamp of last meal
    int             meals_eaten;     // Count of meals consumed
    pthread_t       thread;          // Thread identifier
    t_data          *t_data;         // Reference to shared data
    pthread_mutex_t *left_fork;      // Left fork pointer
    pthread_mutex_t *right_fork;     // Right fork pointer
} t_philo;

typedef struct s_data
{
    long            num_of_philos;   // Number of philosophers
    long            time_to_die;     // Starvation timeout (ms)
    long            time_to_eat;     // Eating duration (ms)
    long            time_to_sleep;   // Sleeping duration (ms)
    long            must_eat_count;  // Meal requirement (or -1)
    long            start_time;      // Simulation start timestamp
    int             someone_die;     // Death flag
    pthread_mutex_t *forks;          // Array of fork mutexes
    pthread_mutex_t write_mutex;     // Protects output
    pthread_mutex_t death_mutex;     // Protects death state
    t_philo         *philos;         // Philosopher array
} t_data;
```

### Synchronization Strategy

#### Preventing Deadlock

The implementation uses **ordered fork acquisition**:
- Each philosopher acquires forks in a **consistent order** (lower index first)
- This prevents circular wait conditions that cause deadlock

```c
if (left_idx < right_idx)
{
    pthread_mutex_lock(&data->forks[left_idx]);
    pthread_mutex_lock(&data->forks[right_idx]);
}
else
{
    pthread_mutex_lock(&data->forks[right_idx]);
    pthread_mutex_lock(&data->forks[left_idx]);
}
```

#### Critical Sections

- **`write_mutex`**: Protects philosopher state logging to prevent interleaved messages
- **`death_mutex`**: Protects the `someone_die` flag and `last_meal` timestamp
- **Fork mutexes**: Each fork is protected to ensure only one philosopher eats per fork

### Philosopher Lifecycle

1. **Thinking** → Acquire both forks
2. **Eating** → Hold both forks, update `last_meal` timestamp
3. **Release forks** → Place forks back on table
4. **Sleeping** → Wait for sleep duration
5. **Repeat** (or exit if death condition met)

### Monitor Thread (Hecate)

The monitor runs continuously and:
- Checks if any philosopher hasn't eaten within `time_to_die` ms
- Checks if all philosophers have eaten `must_eat_count` times
- Sets the `someone_die` flag when termination condition is met
- Allows philosopher threads to exit gracefully

### Race Condition Fix

**Problem**: Gap between checking death flag and printing state could allow a dead philosopher to still print.

**Solution**: Hold `death_mutex` during the entire print operation to ensure atomicity.

```c
pthread_mutex_lock(&philo->t_data->death_mutex);
if (philo->t_data->someone_die) {
    pthread_mutex_unlock(&philo->t_data->death_mutex);
    return;
}
// ... do critical work (print) while mutex is held
pthread_mutex_unlock(&philo->t_data->death_mutex);
```

---

## Resources

### Classic References

- **Dining Philosophers Problem**: [Wikipedia Article](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- **POSIX Threads (pthreads)**: [Man Pages - pthread](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- **Mutex Documentation**: [pthread_mutex_lock](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- **Synchronization Primitives**: [Operating Systems - Mutex & Semaphores](https://en.wikipedia.org/wiki/Mutex)
- **Thread Safety**: [Thread Safety Best Practices](https://www.gnu.org/software/pth/manual/html_node/Thread-Safety.html)

### Learning Materials

- Dijkstra's original formulation of the problem (1965)
- Operating Systems textbooks covering synchronization
- The Art of Multiprocessor Programming by Herlihy & Shavit

### AI Usage

**No AI tools** were extensively used in this implementation. The project was developed using:
- Direct knowledge of pthreads API
- Classic synchronization patterns from operating systems theory
- Manual debugging and testing with various philosopher counts and timing parameters

If AI tools were used for minor tasks (code formatting, documentation), they were:
- Reviewed for correctness
- Adapted to match project requirements
- Tested to ensure no behavioral changes

---

## Testing

### Quick Tests

**Single philosopher (should die):**
```bash
./philo 1 100 50 50
```

**Two philosophers, tight timing:**
```bash
./philo 2 310 100 100
```

**Multiple philosophers, varies outcome:**
```bash
./philo 4 410 200 200
```

**Stress test with many philosophers:**
```bash
./philo 50 800 200 200 5
```

### Expected Behavior

- ✅ All philosophers should be able to eat if timing allows
- ✅ No philosopher should print after dying
- ✅ Death timestamp should occur within 10ms of actual starvation
- ✅ No segmentation faults or memory leaks
- ✅ Output should not overlap (properly synchronized)

---

## Bonus Part

A bonus implementation using **processes and semaphores** instead of threads and mutexes is available in the `philo_bonus/` directory. The bonus part:

- Uses `fork()` to create separate processes for each philosopher
- Uses semaphores (instead of mutexes) to manage fork state
- Centralizes fork management (all forks are shared resources)
- Follows the same argument structure and output format

---

## Known Limitations

- The simulation may not always prevent starvation with very tight timings (this is inherent to the distributed nature of the problem)
- Death detection has a resolution of ~100µs (monitor thread check frequency)
- Clock resolution depends on system `gettimeofday()` precision

---

## Compilation Flags

The Makefile uses standard 42 norm-compliant flags:
- `-Wall`: Enable all common compiler warnings
- `-Wextra`: Enable extra warnings
- `-Werror`: Treat warnings as errors
- `-I.`: Include current directory for headers

---

## Files Submitted

```
philosophers/
├── Makefile
├── philosophers.h    # Header file with data structures
├── philosophers.c    # Philosopher thread logic
├── hecate.c         # Monitor thread logic
├── eaten.c          # Fork acquisition logic
├── mutex.c          # Mutex initialization
├── utils.c          # Utility functions
├── parsing.c        # Argument parsing
└── README.md        # This file
```

---

## Author

**lleineck** - 42 student

For questions or issues, feel free to collaborate with peers or review the project documentation.

---

## License

This project is part of the 42 curriculum and follows its academic integrity policies.
