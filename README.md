# Philosophers Project

## How to Run

1. Compile the project:
    ```bash
    make
    ```

2. Execute the program:
    ```bash
    ./philo [num_of_philos] [time_to_die] [time_to_eat] [time_to_sleep]
    ```

3. Example:
    ```bash
    ./philo 5 600 200 200
    ```

## Testing

There is a nice tester from Dantonik:
[42-philosophers-tester](https://github.com/dantonik/42-philosophers-tester)

### Windows Users

If you are running it on a Windows environment, convert the `./test.sh` file using:
```bash
dos2unix test.sh

### Questions

How do you give the last fork in the circle of the table?
How do you check if the philo is dead and avoiding to eat?
Do you switch left or right fork in case they are even or odd?
