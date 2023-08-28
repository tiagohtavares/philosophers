<h1 align="center">
	philosophers
</h1>

## About 

This project consists of creating a simulation the <a href="https://en.wikipedia.org/wiki/Dining_philosophers_problem">dining philosophers</a> using threads. 

Each philosopher has to be a thread and each fork must have it's own mutex. The number of philo, meal time, sleep, time to die and number of times to eat is defined as arguments when executing the progam. 
Each philosopher can only grab the fork next to him, either left or right. There can be no deadlock's or data races.

The progam must display what's ocurring such as when a philo grabs a fork , eats or sleep. 
Example : 
```
./philo 4 250 200 100
1 1 has taken a fork
1 1 has taken a fork
1 1 is eating
4 3 has taken a fork
4 3 has taken a fork
4 3 is eating
201 1 is sleeping
201 2 has taken a fork
204 3 is sleeping
204 0 has taken a fork
204 0 has taken a fork
204 0 is eating
204 2 has taken a fork
204 2 is eating
252 1 died
```

## Implementation

I started by initializing all the variables recieved as arguments and checking if they are valid. The second step was to initialize each philosopher thread and the forks mutex. 

The number of forks and mutex's is based on the number of philos.
Since each philo can only grab the adjacent fork , i assign a number to them to keep track of wich mutex they are going to grab. For example if there are 6 philos, philo 0 will try to grab fork 0 and 1, while philo 5 will try to grab fork 5 and 0.
When the number of philos is not pair, this order is reversed, this is done to prevent deadlocks from ocurring. 

Two more mutex are also created, meal and print. These are used to prevent data races when updating each philosopher meal and when printing. 

To keep track of philosopher death's a "manager" is created to check if philosophers have starved to death. It also keeps track of the number of time each philo has eaten if it was passed as an argument. 


## Conclusion

This project helped me understand threads and it's value on more complex progams. It also helped me understood troubleshooting data races and deadlock's caused by the use of threads. 
