<p align="center">
  <img src="https://github.com/mcombeau/mcombeau/blob/main/42_badges/philosopherse.png" />
</p>

# Welcome to Philosophers
Eat, Sleep, Spaghetti, repeat.

This project is about learning how threads work by precisely timing a group of philosophers on when to pick up forks and eat spaghetti without dying from hunger.

## Status
Finished: 12/02/2023<br>
Grade: 100/100%

## Project introduction

This project aims to explore an important topic in computer science such as multithreading using UNIX threads and synchronizing primitive mutex.

This project is based on a problem formulated by Dijkstra - the Dining Philosophers Problem

### Common Instructions
- This project must be written in C.
- The project must be written in accordance with the Norm.
- All functions should not quit unexpectedly - segmentation fault, bus error, double free, etc.
- All heap-allocated memory space must be properly freed when necessary. No leaks will be tolerated.
- You must submit a Makefile which will compile your source files to the required output with the flags -Wall, -Wextra, and -Werror, use cc, and your Makefile must not relink.
- Your Makefile must at least contain the rules $(NAME), all, clean, fclean and re.

### Project Overview
- One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternatively eat, think, or sleep. While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping; and, of course, while sleeping, they are not eating nor thinking.
- There are also forks on the table. There are as many forks as philosophers.
- Because serving and eating spaghetti with only one fork is very inconvenient, a philosopher takes their right and their left forks to eat, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die.
- No need to say that philosophers should avoid dying!

### Global rules
- **Global variables are forbidden!**

Program input:

- Your(s) program(s) should take the following arguments:
  - number_of_philosophers: The number of philosophers and also the number of forks.
  - time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
  - time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
  - time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
  - number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
- Each philosopher has a number ranging from 1 to number_of_philosophers.
- Philosopher number 1 sits next to philosopher number number_of_philosophers.
Any other philosopher number N sits between philosopher number N - 1 and philoso-
pher number N + 1.

Program output:

Any state change of a philosopher must be formatted as follows:
- timestamp_in_ms X has taken a fork
- timestamp_in_ms X is eating
- timestamp_in_ms X is sleeping
- timestamp_in_ms X is thinking
- timestamp_in_ms X died

Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.

A displayed state message should not be mixed up with another message.
A message announcing a philosopher died should be displayed no more than 10 ms
after the actual death of the philosopher.

**Your program must not have any data races.**

## Original problem definition

The Dining Philosophers Problem is a classic computer science problem that illustrates the challenges of concurrency and resource allocation in distributed systems. The problem is named after a hypothetical scenario in which a group of philosophers is sitting around a circular table with one fork between each pair of adjacent philosophers, and a plate of food in the center of the table.

Each philosopher alternates between two activities: eating and thinking. To eat, a philosopher must pick up both forks adjacent to them. Once they are finished eating, they must put down the forks so that they can be used by their neighbors.

The challenge is to design a solution that prevents deadlocks and starvation.

### Deadlock? What is it?

In computer science, a deadlock is a situation where two or more processes are blocked and waiting for each other to release a resource that they need to proceed, resulting in a standstill where none of the processes can make progress.

Let's imagine a scenario where there are five philosophers seated at a circular table, each with one fork to their left and one fork to their right. In the beginning, all philosophers are thinking and have not picked up any forks.

Now let's say that philosopher 1 decides to pick up the fork to their left, philosopher 2 decides to pick up the fork to their right, philosopher 3 picks up the fork to their left, philosopher 4 picks up the fork to their right, and philosopher 5 picks up the fork to their left.

At this point, all five philosophers have one fork and are waiting for their neighbor to release the other fork they need to eat. However, since each philosopher is holding onto a fork that their neighbor needs, none of the philosophers can proceed with eating.

<img src="https://github.com/AlexMitcul/philosophers/blob/main/img/1.jpeg" width="600">

### Dijkstra's solution

Dijkstra's solution to the dining philosopher's problem is one of the classic algorithms for preventing deadlocks in a concurrent system where multiple processes compete for a limited set of resources. The algorithm is named after Dutch computer scientist Edsger W. Dijkstra, who first proposed it in 1965.

Dijkstra's solution is based on the idea of introducing a strict ordering of the resources, such that each philosopher can only pick up the fork of lower priority before picking up the fork of higher priority. In other words, a philosopher can only pick up the fork to their left if the fork to their right is not currently in use by a higher-priority philosopher.

The algorithm works as follows:

- Each philosopher is assigned a number, from 1 to N, where N is the number of philosophers.
- Each philosopher first tries to pick up the fork with the lower number.
- If the philosopher cannot pick up the lower-numbered fork because it is currently in use by another philosopher, they put down the fork they are holding and wait for a short time.
- After waiting, the philosopher tries again to pick up the fork with the lower number.
- If the philosopher successfully picks up the lower-numbered fork, they try to pick up the higher-numbered fork.

<img src="https://github.com/AlexMitcul/philosophers/blob/main/img/2.jpeg" width="600">

By enforcing this ordering of resource acquisition, Dijkstra's solution ensures that no two philosophers will be able to pick up both forks at the same time, thus preventing deadlocks. However, the solution may still result in starvation, where a philosopher is repeatedly passed over for the opportunity to eat if other higher-priority philosophers are constantly using the forks.

### Optimization the Dijkstra's solution

To prevent starvation, where a philosopher is repeatedly passed over for the opportunity to eat if other higher-priority philosophers are constantly using the forks.

Let's make it a condition that each philosopher with an odd id comes to the table a little late. This will help to distribute the forks evenly to all the seated philosophers and prevent suboptimal behavior.

### Step 1
<img src="https://github.com/AlexMitcul/philosophers/blob/main/img/4.jpeg" width="600">

### Step 2

<img src="https://github.com/AlexMitcul/philosophers/blob/main/img/3.jpeg" width="600">

## What need to know to realize that

## UNIX Threads

Unix threads are a type of lightweight process that allows for the concurrent execution of multiple tasks within a single process. Threads are often used to implement parallelism in programs that can benefit from the simultaneous execution of multiple tasks, such as web servers, database servers, and multimedia applications.

In Unix-based operating systems, threads are created and managed by the operating system's kernel or by a thread library such as pthreads. Each thread has its own set of registers, stack, and program counters, but shares the same address space and other system resources with other threads in the same process. This allows threads to communicate and synchronize with each other more efficiently than processes, which require inter-process communication mechanisms such as pipes or sockets.

One advantage of using threads is that they can take advantage of multiple CPUs or cores on a system, allowing for true parallelism and potentially faster execution times. However, thread-based programming can also be more challenging than single-threaded programming, as threads can introduce issues such as race conditions, deadlocks, and thread starvation. These issues can be mitigated through careful design and the use of synchronization mechanisms such as mutexes, semaphores, and condition variables.

### How to use threads

pthread_create is a function used to create a new thread in a multithreaded program. Here is how it works:

- The function takes as input several parameters, including a pointer to a pthread_t variable, which will be used to store the ID of the new thread, a pointer to a pthread_attr_t variable, which is used to specify various attributes of the new thread, a pointer to a function that will be executed by the new thread, and an optional argument to pass to the function.

- The function creates a new thread with the specified attributes and assigns a unique ID to the thread, which is stored in the pthread_t variable that was passed as input.

- The new thread starts executing the function that was specified as input, passing in the optional argument.

- After the new thread is created, both the parent thread and the new thread can execute concurrently, each performing its own set of instructions.


pthread_detach is a function used to detach a thread that was previously created with the pthread_create function. Here is how it works:

- The function takes as input a pthread_t variable that represents the thread to be detached.

- The function detaches the thread from the process, which allows the thread to continue executing independently of the process.

- Once the thread is detached, it cannot be joined with another thread using the pthread_join function.

- Any resources that were associated with the thread are released and made available for reuse by the system.

pthread_join is a function used to wait for a thread to terminate and to obtain the exit status of the thread. Here is how it works:

- The function takes as input a pthread_t variable that represents the thread to be joined and a pointer to a variable that will store the exit status of the thread.

- The function blocks the calling thread until the specified thread has terminated.

- Once the specified thread has terminated, the function sets the value of the exit status variable to the exit status of the thread.

- Any resources that were associated with the thread are released and made available for reuse by the system.

For more information use [man page](https://man7.org/linux/man-pages/man7/pthreads.7.html)

### Which of them do I need to use?

The main difference between pthread_join and pthread_detach is that pthread_join is used to wait for a thread to terminate and obtain its exit status, while pthread_detach is used to detach a thread from the process so that it can continue executing independently.

Here are some more details on the differences between the two functions:

- pthread_join: When a thread is created with pthread_create, it is said to be "joinable" by default, which means that another thread can wait for it to terminate using pthread_join. When a thread is joined with pthread_join, the calling thread blocks until the specified thread has terminated. The exit status of the specified thread is then obtained and stored in a variable passed as a parameter. Once the specified thread has been joined, its resources are automatically released. If the specified thread has already terminated, pthread_join returns immediately.

- pthread_detach: When a thread is detached with pthread_detach, it is removed from the process's thread list and is no longer joinable. Once a thread is detached, it can continue executing independently of the process, and its resources are automatically released when it terminates. If a thread is detached and later attempts to be joined using pthread_join, the result is undefined and may cause a segmentation fault or other error.

In summary, if you need to obtain the exit status of a thread or ensure that it has terminated before proceeding, you should use pthread_join. If you want to detach a thread so that it can continue executing independently, you should use pthread_detach.


## Mutex

A mutex, short for "mutual exclusion", is a synchronization primitive used to ensure that only one thread at a time can access a shared resource, such as a variable or a data structure, in a multithreaded program. A mutex is essentially a lock that a thread can acquire before accessing a shared resource, and release after it has finished accessing the resource.

The use of a mutex prevents multiple threads from simultaneously modifying or reading the same resource, which could result in data corruption, race conditions, and other synchronization issues. By ensuring that only one thread can access the resource at a time, a mutex provides a way for threads to coordinate and communicate with each other without interfering with each other's operations.

In most programming languages and operating systems, a mutex is implemented as a data structure that contains a lock or flag indicating whether the resource is currently being used by a thread. A thread that wants to access the resource first tries to acquire the mutex lock by calling a mutex function, which checks whether the lock is available. If the lock is available, the thread acquires the lock and can proceed with accessing the resource. If the lock is not available, the thread is blocked until the lock becomes available, at which point it can acquire the lock and proceed.

Once a thread has finished accessing the resource, it releases the mutex lock by calling a mutex function, which frees the lock and allows other threads to acquire it. By using mutexes, programmers can write multithreaded programs that are thread-safe, efficient, and free from synchronization issues.

### Ok, do I really need to use mutex?

Short answer:

Yes, for every variable that one of your threads will write some data in that variable, and the other thread will read/write data from there, you need to protect access to this variable using a mutex.

Long answer:

You need to use a mutex in a multithreaded program to ensure that multiple threads do not simultaneously access or modify the same shared resource, such as a variable, data structure, or device. Without a mutex, multiple threads could access the resource concurrently, leading to data races, synchronization issues, and other problems.

Here are some specific reasons why you might need to use a mutex:

- To prevent data races: A data race occurs when two or more threads access or modify the same data without proper synchronization. Data races can result in undefined behavior, such as inconsistent or corrupt data, crashes, or other synchronization issues. By using a mutex, you can ensure that only one thread at a time can access or modify the data, preventing data races.

- To ensure consistency: In some multithreaded programs, it is essential to ensure that certain operations are performed atomically, without interruption from other threads. For example, if one thread is updating a shared data structure, it might need to temporarily block other threads from accessing or modifying the structure until the update is complete. A mutex can provide this kind of atomicity and ensure that the shared data structure remains consistent.

- To manage access to resources: In some multithreaded programs, multiple threads might need to access a shared resource, such as a file, network socket, or device. A mutex can be used to manage access to the resource, ensuring that only one thread at a time can access it and preventing conflicts and synchronization issues.

### How to use mutex

The pthread_mutex_init function is used to initialize a mutex object in a multithreaded program. It creates a new mutex object and sets its attributes to the specified values.

Here is how pthread_mutex_init works:

- The function takes as input a pointer to a mutex object, which is a data structure that contains information about the mutex, such as its state, owner, and other attributes.

- The function also takes as input a pointer to a mutex attribute object, which contains information about the attributes of the mutex, such as its type, scope, and protocol. If this argument is set to NULL, the mutex is initialized with default attributes.

- The pthread_mutex_init function initializes the mutex object with the specified attributes. If the mutex attribute object is NULL, the function initializes the mutex with default attributes.

- The function returns an error code if the initialization fails, such as if there is insufficient memory to create the mutex object, or if the mutex attribute object contains invalid values.

In our project, we don't have access to functions that initialize attributes for mutex and we need to pass NULL in this case.

pthread_mutex_lock and pthread_mutex_unlock are functions that are used to control access to a shared resource in a multithreaded program by acquiring and releasing a mutex lock.

Here is how pthread_mutex_lock works:

- The function takes as input a pointer to a mutex object, which is a data structure that contains information about the mutex, such as its state, owner, and other attributes.

- The function attempts to acquire the mutex lock. If the lock is already held by another thread, the calling thread will be blocked until the lock becomes available.

- Once the lock is acquired, the function returns, and the calling thread can access the shared resource safely.

pthread_mutex_destroy is a function used to destroy a mutex object that was previously initialized with pthread_mutex_init. Here is how it works:

- The function takes as input a pointer to a mutex object, which is a data structure that contains information about the mutex, such as its state, owner, and other attributes.

- The function destroys the mutex object and releases any resources that were associated with it.

- After the mutex object is destroyed, it can no longer be used, and any attempt to use it will result in undefined behavior.

For more information use [man page](https://linux.die.net/man/3/pthread_mutex_init)

```cpp
#include <pthread.h>

pthread_mutex_t mutex;

void *thread_function(void *arg) {
    // Acquire the mutex lock
    pthread_mutex_lock(&mutex);
    // Critical section
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    // Initialize the mutex object
    pthread_mutex_init(&mutex, NULL);

    // Create a new thread
    pthread_t thread;
    pthread_create(&thread, NULL, thread_function, NULL);

    // Acquire the mutex lock
    pthread_mutex_lock(&mutex);
    // Critical section
    pthread_mutex_unlock(&mutex);

    // Wait for the thread to finish
    pthread_join(thread, NULL);

    // Destroy the mutex object when you are done using it
    pthread_mutex_destroy(&mutex);

    return 0;
}
```

<img src="https://github.com/AlexMitcul/philosophers/blob/main/img/scheme1.jpeg" width="800">
<img src="https://github.com/AlexMitcul/philosophers/blob/main/img/scheme2.jpeg" width="800">

-----
| amitcul@student.42porto.com | ![LinkedIn](https://www.linkedin.com/in/alex-mitcul/) | ![Telegram](t.me/MitculAlex) |
