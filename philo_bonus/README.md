### Note
This program is a bit different from the one I've submitted. I encountered an issue during my evaluations with the way I monitored the death of a philosopher, the simulation did not stop on cases such as:

```
./philo_bonus 4 310 200 100
./philo_bonus 5 800 500 275
./philo_bonus 12 400 200 250
```

This version is capable of handling such cases however it introduced a new problem which is one memory leak on every child process due to the use of pthreads.
