# 1337_philosophers
1337 philosophers common-core project !

# AI explanation :

Of course, I can provide a detailed project approach for the "Philosophers" project. Here's a breakdown of the concepts, structure, and execution flow to help your friend understand it completely.

### Project Overview: The Dining Philosophers Problem

This project is a classic computer science problem called the **Dining Philosophers**. The goal is to simulate a group of philosophers sitting around a table, who alternate between thinking and eating. The challenge lies in resource allocation: there's one fork between each philosopher, and to eat, a philosopher needs to pick up both their left and right forks. The primary goal is to write a program that allows the philosophers to eat without two philosophers grabbing the same fork simultaneously (a data race) and without getting into a situation where no one can eat (a deadlock).

### Core Concepts

This project revolves around three main technical concepts:

1.  **Multithreading:** Each philosopher is represented by a separate thread of execution. This allows them to "act" concurrently. This project uses the **pthreads (POSIX threads)** library, a standard for creating and managing threads in C.

2.  **Mutexes (Mutual Exclusion):** To prevent two philosophers from picking up the same fork at the same time, we use mutexes. A mutex is like a lock. Before a philosopher can pick up a fork, they must "lock" it. If another philosopher already has it locked, the second philosopher must wait until it's unlocked. This ensures exclusive access to a shared resource.

3.  **Synchronization:** The entire simulation needs to be carefully synchronized. All philosophers need to start at the same time, their actions (eating, sleeping) need to take a specified amount of time, and there needs to be a central "monitor" checking for when the simulation should end (either because a philosopher dies of starvation or because everyone has eaten enough).

### Step-by-Step Project Approach

Here is a breakdown of how the provided code is structured and the steps it takes to solve the problem.

#### Step 1: Understanding the Input and Initialization (`main.c` and `init.c`)

The program starts by taking command-line arguments:
*   `number_of_philosophers`: How many philosophers are at the table.
*   `time_to_die`: The time in milliseconds a philosopher can go without eating before they die.
*   `time_to_eat`: The time in milliseconds it takes for a philosopher to eat.
*   `time_to_sleep`: The time in milliseconds a philosopher sleeps after eating.
*   `[number_of_times_each_philosopher_must_eat]`: (Optional) If provided, the simulation stops once every philosopher has eaten this many times.

The `main` function first validates the number of arguments. Then, it calls `init_data` to set up the simulation environment. Here’s the critical order of initialization in `init_data`:

1.  **Parse Arguments:** The input strings are converted to numbers using `ft_atol`.
2.  **Allocate Memory for Philosophers:** It allocates memory to hold all the `t_philo` structures.
3.  **Initialize Forks and Locks:**
    *   It allocates memory for an array of `pthread_mutex_t`, one for each fork.
    *   It initializes each fork mutex using `pthread_mutex_init`.
    *   It also initializes two other crucial mutexes: `print_lock` (to prevent scrambled output from multiple threads printing at once) and `data_lock` (to protect shared data like the simulation end flag).
4.  **Initialize Each Philosopher's Data:** With the forks created, it can now populate each philosopher's structure (`t_philo`), assigning them an ID and pointers to their left and right forks.

#### Step 2: The Philosopher's Life (`routine.c`)

Each philosopher thread executes the `philo_routine` function. This is an infinite loop that represents the philosopher's life cycle: **eat -> sleep -> think**.

1.  **The `philo_eat` function is the most critical part:**
    *   **Deadlock Prevention:** A simple strategy to avoid deadlock is to have even-numbered philosophers pick up their right fork first, while odd-numbered philosophers pick up their left fork first. This breaks the "circular wait" condition that leads to deadlock, where everyone is waiting for the person on their right to release a fork.
    *   **Locking Forks:** A philosopher locks their first fork, prints a "has taken a fork" status, and then locks the second fork.
    *   **Eating:** Once both forks are held, the philosopher is "eating." They update their `last_meal_time` and increment their `meals_eaten` count. These updates are protected by the `data_lock` because the monitor thread is also reading this data.
    *   **Unlocking Forks:** After eating for `time_to_eat`, the philosopher releases (unlocks) both forks, making them available to their neighbors.

2.  **Sleeping and Thinking:** After eating, the philosopher sleeps for `time_to_sleep` and then prints that they are "thinking." The loop then repeats.

#### Step 3: The Monitor (`routine.c`)

While the philosopher threads are running, the main thread runs the `run_monitor` function. This function is the "referee" of the simulation. It runs in a loop and continuously checks for two conditions to end the simulation:

1.  **Death Check:** The monitor iterates through each philosopher and checks if the time since their last meal is greater than `time_to_die`.
    *   To do this safely, it locks the `data_lock` before reading a philosopher's `last_meal_time`.
    *   If a philosopher has died, it sets the `simulation_should_end` flag to 1, prints the "died" message, and returns.

2.  **Meal Count Check:** If the optional `num_must_eat` argument was given, the monitor checks if all philosophers have eaten at least that many times.
    *   It assumes they all have, then loops through them. If it finds one who hasn't, it resets the flag and continues.
    *   If all philosophers have eaten enough, it sets the `simulation_should_end` flag to 1 and returns.

The `usleep(1000)` at the end of the monitor's loop is important to prevent it from constantly using the CPU, giving the philosopher threads more time to run.

#### Step 4: Time Management and Responsive Sleeping (`time_utils.c`)

Precise time management is key.

*   **`get_current_time()`:** This function uses `gettimeofday` to get the current time in milliseconds. This is used to set the start time of the simulation and to check for philosopher deaths.
*   **`cancellable_sleep()`:** Instead of a single `usleep` call for eating or sleeping, this function sleeps in small increments. After each small sleep, it checks the `simulation_should_end` flag. This is crucial because if one philosopher dies, all other philosophers should stop what they are doing immediately, not wait for their current eating or sleeping period to finish.

#### Step 5: Starting and Ending the Simulation (`main.c` and `routine.c`)

The `start_simulation` function orchestrates the beginning and end of the simulation:

1.  **Create Threads:** It loops through the philosophers and creates a thread for each one using `pthread_create`, passing the `philo_routine` as the function to execute.
2.  **Run the Monitor:** After launching all the philosopher threads, the main thread calls `run_monitor`.
3.  **Join Threads:** When `run_monitor` returns (because a philosopher died or everyone is full), the `start_simulation` function then calls `pthread_join` for each philosopher thread. This makes the main thread wait for all philosopher threads to finish their execution before moving on.

#### Step 6: Cleanup (`init.c`)

The `cleanup` function is called at the very end to release all allocated resources. To be robust, it checks if pointers are not NULL before trying to free or destroy them.

*   It destroys every mutex that was initialized for the forks.
*   It frees the memory allocated for the forks array.
*   It destroys the `print_lock` and `data_lock`.
*   It frees the memory allocated for the philosophers array.

This prevents memory leaks and ensures the program exits cleanly.

### Summary for Your Friend

To understand this project, you can think of it in these main parts:

1.  **Setup:** Read the rules from the command line and set the table (initialize data structures, mutexes).
2.  **The Philosophers:** Each philosopher runs in their own thread, trying to eat, sleep, and think. They must lock forks to eat, and they follow a special rule (even/odd) to avoid getting stuck.
3.  **The Supervisor:** A main "monitor" thread watches the philosophers. It ends the simulation if someone dies from waiting too long or if everyone has eaten the required number of meals.
4.  **The Clock:** Time is carefully tracked in milliseconds to enforce the rules about eating, sleeping, and dying. The sleep function is special so that it can be interrupted if the simulation needs to end early.
5.  **Cleanup:** After the simulation is over, everything is cleaned up (mutexes destroyed, memory freed).