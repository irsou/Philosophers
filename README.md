# Philosophers


## 🚀 Purpose


## Aditional details
- Threads
A thread is sort of a separate "path of execution" within your program. A regular program has a single thread and makes things in a row (sequentially) in it, but several threads can be created in the same program running in parallel, so various things can be made at the same time (concurrently).

- Mutexes (Mutual Exclusion)
A mutex is like a "lock" that protects shared resources. Only a single thread is allowed to "hold the key" at a time.

# Tests

- Check the code of Philo for the following things and ask for an explanation.
- Check if there is one thread per philosopher.
- Check there's only one fork per philosopher.
- Check if there is a mutex per fork and that it's used to check the fork value and/or change it.
- Check the output should never produce a scrambled view.
- Check how the death of a philosopher is checked and if there is a mutex to protect that a philosopher dies and start
eating at the same time.
- Do not test with more than 200 philosophers
- Do not test with time_to_die or time_to_eat or time_to_sleep under 60 ms
- Test with 1 800 200 200, the philosopher should not eat and should die!
- Test with 5 800 200 200, no one should die!
- Test with 5 800 200 200 7, no one should die and the simulation should stop when all the philosopher has eaten at
least 7 times each.
- Test with 4 410 200 200, no one should die!
- Test with 4 310 200 100, a philosopher should die!
- Test with 2 philosophers and check the different times (a death delayed by more than 10 ms is unacceptable).
- Test with your values to check all the rules. Check if a philosopher dies at the right time if they don't steal forks, etc.

## ⚙️ How to compile

##  How to debug
  
## 🌐 Related links
https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/
https://www.linkedin.com/pulse/guide-using-mutual-exclusion-locks-mutex-pthreads-c-yamil-garcia

##  🤝Contributions
Contributions are welcome! Open an issue or submit a pull request to suggest improvements or fixes.


