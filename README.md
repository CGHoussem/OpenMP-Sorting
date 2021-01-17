# Parallel Sorting (using: OpenMP)
School project developed using C and Python.

## Installing dependencies for python plotting!
```bash
    # Navigate to plots directory
    $ cd TriParallele/plots

    # Create the virtual environement (venv)
    $ python3 -m venv venv
    
    # Activating the virtual environement
    $ source venv/bin/activate

    # Install required python modules
    (venv)$ pip install -r requirements.txt
``` 

## Building the C project
Use the MAKEFILE to build the project.
```bash
    $ cd TriParallele/src
    $ make clean
    $ make
``` 

## Executing the project
### Part 1
Executing the C compiled object to extract the performances data into a csv file called 'performances.csv' in the same directory.
```bash
    $ cd TriParallele/src
    
    # ./program filename[.csv]
    $ ./program performance.csv
```
***Note: The execution of the program might take a couple of hours depending on your machine.***

### Part 2
Executing the Python script to make the plots (charts).

***Keep in mind that this part requires the installed dependencies mentionned above!***
```bash
    $ cd TriParallele/plots

    # Activating the virtual environment
    $ source venv/bin/activate

    # Executing the script
    (venv)$ python plot.py

    # Deactivating the virtual environment
    (venv)$ deactivate
```

Managing the development tasks in a [Trello Table](https://trello.com/c/5taH9aZz/10-programmation-parall%C3%A8le-et-distribu%C3%A9e).
